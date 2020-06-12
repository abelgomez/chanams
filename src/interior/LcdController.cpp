#include "interior/LcdController.h"

#define BACKLIGHT_TIMEOUT 10
#define GOTO_FIRST_SCREEN_TIMEOUT 60

#define DEPOSIT_FULL_ALARM_SCREEN -2
#define DEAD_ALARM_SCREEN -1
#define SENSORS_SCREEN 0
#define BATTERY_SCREEN 1
#define WIFI_SCREEN 2
#define SERVICE_SCREEN 3
#define DATE_TIME_SCREEN 4

#define NUM_SCREENS 5

DisableDisplayTimer::DisableDisplayTimer(unsigned long timeoutSeconds, LcdController *controller, Scheduler &scheduler)
    : Task(timeoutSeconds * 1000, TASK_ONCE, &scheduler, false),
      controller(controller) {
    this->enableDelayed();
    controller->backlight();
}

void DisableDisplayTimer::restore() {
    this->restartDelayed();
    controller->backlight();
}

bool DisableDisplayTimer::Callback() {
    controller->noBacklight();
    return true;
}

ShowHomeScreenTimer::ShowHomeScreenTimer(unsigned long timeoutSeconds, LcdController *controller, Scheduler &scheduler)
    : Task(timeoutSeconds * 1000, TASK_ONCE, &scheduler, false),
      controller(controller) {
    this->enableDelayed();
}

void ShowHomeScreenTimer::restore() {
    this->restartDelayed();
}

bool ShowHomeScreenTimer::Callback() {
    controller->showScreen(SENSORS_SCREEN, true);
    return true;
}

LcdController::LcdController(uint8_t sdaPin, uint8_t sclPin, Switch &button, Scheduler &scheduler)
    : Task(100, TASK_FOREVER, &scheduler, true),
      lcd(0x27, 16, 2),
      button(button),
      disableDisplayTimer(BACKLIGHT_TIMEOUT, this, scheduler),
      showHomeScreenTimer(GOTO_FIRST_SCREEN_TIMEOUT, this, scheduler) {
    Wire.begin(sdaPin, sclPin);
    lcd.init();
    byte degreeSymbol[] = {B11100, B10100, B11100, B00000, B00000, B00000, B00000, B00000};
    lcd.createChar(1, degreeSymbol);
};

void LcdController::setTemperature(float temperature) {
    Serial.println("Set temperature");
    int nextScreen = currentScreen;
    if (currentScreen >= 0 && isnan(this->temperature)) {
        // First time we set this value while showing a normal screen
        nextScreen = SENSORS_SCREEN;
    }
    this->temperature = temperature;
    showScreen(nextScreen);
}

void LcdController::setHumidity(float humidity) {
    Serial.println("Set humidity");
    int nextScreen = currentScreen;
    if (currentScreen >= 0 && isnan(this->humidity)) {
        // First time we set this value while showing a normal screen
        nextScreen = SENSORS_SCREEN;
    }
    this->humidity = humidity;
    showScreen(nextScreen);
}

void LcdController::setDepositFull(boolean full) {
    Serial.println("Set deposit full");
    int nextScreen = currentScreen;
    if (this->depositFull != DEPOSIT_FULL && full) {
        // Switching from empty to full while showing anything
        nextScreen = DEPOSIT_FULL_ALARM_SCREEN;
    } else if (this->depositFull == DEPOSIT_FULL && !full && currentScreen < 0) {
        // Switching from full to empty while showing warning
        nextScreen = SENSORS_SCREEN;
    } else if (this->depositFull == DEPOSIT_UNKNOWN && currentScreen >= 0) {
        // First time we set this value while showing a normal screen
        nextScreen = SENSORS_SCREEN;
    }
    this->depositFull = full ? DEPOSIT_FULL : DEPOSIT_EMPTY;
    showScreen(nextScreen);
}

void LcdController::setBatteryVccThreshold(float batteryVccThreshold) {
    this->batteryVccThreshold = batteryVccThreshold;
}

void LcdController::setBatteryVcc(float batteryVcc) {
    Serial.println("Set battery Vcc");
    this->batteryVcc = batteryVcc;
    showScreen(currentScreen);
}

void LcdController::setWifi(std::string wifi) {
    this->wifi = wifi;
}

void LcdController::setHostname(std::string hostname) {
    this->hostname = hostname;
}

void LcdController::setIP(std::string ip) {
    this->ip = ip;
}

void LcdController::setListeningPort(uint listeningPort) {
    this->listeningPort = listeningPort;
}

void LcdController::setDateTime(std::string date, std::string time) {
    this->date = date;
    this->time = time;
    if (currentScreen == DATE_TIME_SCREEN) {
        showScreen(currentScreen);
    }
}

void LcdController::showBooting() {
    lcd.backlight();
    show("Iniciando...");
}
void LcdController::showConnectToPortal(std::string portalName) {
    lcd.backlight();
    show("Conecta a", portalName);
}

void LcdController::showConnecting() {
    lcd.backlight();
    show("Conectando a", "red WiFi...");
}

void LcdController::showSleeping() {
    lcd.backlight();
    show("Conexion fallida", "Durmiendo ZzZz");
}

void LcdController::showDeadAlarm() {
    Serial.println("Show dead alarm");
    this->depositFull = DEPOSIT_EMPTY; // To make sure that if the deposit is full
                               // after connection restore the alarm is raised again
    showScreen(DEAD_ALARM_SCREEN);
}

void LcdController::showStatus() {
    Serial.println("Show status");
    if (currentScreen >= DEAD_ALARM_SCREEN) {
        showScreen(SENSORS_SCREEN);
    }
}

void LcdController::show(std::string line1) {
    show(line1, "");
}

void LcdController::show(std::string line1, std::string line2) {
    lcd.clear();
    {
        uint spaces = (16 - line1.length()) / 2;
        lcd.setCursor(spaces, 0);
        lcd.print(line1.c_str());
    }
    {
        uint spaces = (16 - line2.length()) / 2;
        lcd.setCursor(spaces, 1);
        lcd.print(line2.c_str());
    }
}

void LcdController::showScreen(int screen) {
    showScreen(screen, false);
}

void LcdController::showScreen(int screen, boolean silent) {
    Serial.println("Showing screen " + String(screen));

    if (screen < 0) {
        disableDisplayTimer.disable();
        showHomeScreenTimer.disable();
        lcd.backlight();
    } else if (currentScreen != screen && !silent) {
        disableDisplayTimer.restore();
        showHomeScreenTimer.restore();
    }
    currentScreen = screen;

    switch (screen) {
        case DEPOSIT_FULL_ALARM_SCREEN:
            show("!!! ALERTA !!!", "DEPOSITO LLENO");
            break;
        case DEAD_ALARM_SCREEN:
            show("!!! ALERTA !!!", "CONEXION PERDIDA");
            break;
        case SENSORS_SCREEN:
            if (!std::isnan(temperature) && !std::isnan(humidity) && depositFull != DEPOSIT_UNKNOWN) {
                show(depositFull ? "Deposito LLENO" : "Deposito OK",
                     toOneDecimal(temperature) + "\x01" + "C / " + toOneDecimal(humidity) + "%");
            } else {
                Serial.println("Missing data to show screen " + String(screen) + "... Showing next");
                showScreen(screen + 1);
            }
            break;
        case BATTERY_SCREEN:
            if (!std::isnan(batteryVcc)) {
                show(batteryVcc < batteryVccThreshold ? "Bateria BAJA" : "Bateria OK",
                     ("(" + String(batteryVcc) + "V)").c_str());
            } else {
                Serial.println("Missing data to show screen " + String(screen) + "... Showing next");
                showScreen(screen + 1);
            }
            break;
        case WIFI_SCREEN:
            show(wifi, hostname);
            break;
        case SERVICE_SCREEN:
            show(ip, String(listeningPort).c_str());
            break;
        case DATE_TIME_SCREEN:
            show(date, time);
            break;
        default:
            showScreen(0);
            break;
    }
}

std::string LcdController::toOneDecimal(float value) {
    char buf[16];
    snprintf(buf, 16, "%.1f", value);
    return buf;
}

void LcdController::backlight() {
    lcd.backlight();
}

void LcdController::noBacklight() {
    lcd.noBacklight();
}

bool LcdController::Callback() {
    if (button.closed()) {
        if (!buttonWasPressed) {
            buttonWasPressed = true;
            if (currentScreen >= 0) {
                // If no alarm is being shown
                if (disableDisplayTimer.isEnabled()) {
                    // Go to next screen only if backlight is on
                    showScreen((currentScreen + 1) % NUM_SCREENS);
                }
                // And turn on the screens and enable the timers. This
                // should be done after the previous check
                disableDisplayTimer.restore();
                showHomeScreenTimer.restore();
            }
        }
    } else {
        buttonWasPressed = false;
    }
    return true;
}
