#include <Arduino.h>

#define _TASK_OO_CALLBACKS

#include <ESP8266mDNS.h>
#include <TaskScheduler.h>
#include <ezTime.h>
#include <uMQTTBroker.h>

#include "ConnectionManager.h"
#include "GlobalConstants.h"
#include "Switch.h"
#include "interior/Alarms.h"
#include "interior/LcdController.h"
#include "interior/LedController.h"
#include "interior/InteriorConfigManager.h"
#include "interior/Semaphore.h"

#define RED_LED D8
#define ORANGE_LED D6
#define GREEN_LED D7
#define BUZZER D1
#define BUTTON D2
#define SDA D4
#define SCL D3

#define WIFI_TIMEOUT 15000

class Dummy {
public:
    Dummy() {
        Serial.begin(9600);
        Serial.println("");
    }
} dummy;

Scheduler scheduler;

InteriorConfigManager configManager;
ConnectionManager connectionManager;

Switch button(BUTTON);
Semaphore semaphore(RED_LED, ORANGE_LED, GREEN_LED, BUZZER, scheduler);
Alarms alarms(BUZZER, button, configManager, scheduler);
LcdController lcdController(SDA, SCL, button, scheduler);

class SlaveTimer : public Task {
public:
    SlaveTimer(uint timeoutMinutes, Scheduler &scheduler) : Task(timeoutMinutes * 60 * 1000, TASK_ONCE, &scheduler, false) {
        this->restore();
    }
    void restore() {
        Serial.println("Slave timer restored");
        this->restartDelayed();
        alarms.dead(false);
        semaphore.dead(false);
        lcdController.showStatus();
    }
    bool Callback() {
        Serial.println("Callback for slave timer invoked");
        alarms.dead(true);
        semaphore.dead(true);
        lcdController.showDeadAlarm();
        return true;
    }
};

SlaveTimer slaveTimer(configManager.getTimeoutMinutes(), scheduler);

class Broker : public uMQTTBroker {
public:
    Broker(uint16_t portno = 1883, uint16_t max_subscriptions = 30, uint16_t max_retained_topics = 30)
        : uMQTTBroker(portno, max_subscriptions, max_retained_topics) {}

    virtual bool onConnect(IPAddress addr, uint16_t client_count) {
        Serial.println(addr.toString() + " connected");
        return true;
    }

    virtual void onData(String topic, const char *data, uint32_t length) {
        String value = std::string(data, length).c_str();
        Serial.println("Received topic '" + topic + "' with data '" + value + "'");
        if (topic.startsWith(TOPIC_CHANAMS)) {
            slaveTimer.restore();
            if (topic.equals(TOPIC_CHANAMS_DEPOSIT)) {
                if (value.equalsIgnoreCase("false")) {
                    alarms.depositFull(false);
                    semaphore.depositFull(false);
                    lcdController.setDepositFull(false);
                } else if (value.equalsIgnoreCase("true")) {
                    alarms.depositFull(true);
                    semaphore.depositFull(true);
                    lcdController.setDepositFull(true);
                } else {
                    Serial.println("Unexpected value for " + topic + ": " + value);
                }
            } else if (topic.equals(TOPIC_CHANAMS_TEMPERATURE)) {
                lcdController.setTemperature(value.toFloat());
            } else if (topic.equals(TOPIC_CHANAMS_HUMIDITY)) {
                lcdController.setHumidity(value.toFloat());
            } else if (topic.equals(TOPIC_CHANAMS_VCC)) {
                lcdController.setBatteryVcc(value.toFloat());
                if (value.toFloat() < configManager.getBatteryVccThreshold()) {
                    alarms.batteryLow(true);
                    semaphore.batteryLow(true);
                } else {
                    alarms.batteryLow(false);
                    semaphore.batteryLow(false);
                }
            }
        }
    }
};

Broker broker(configManager.getListeningPort());

class UpdateTask : public Task {
private:
    int hour = -1;
    int minute = -1;

public:
    UpdateTask(Scheduler &scheduler) : Task(100, TASK_FOREVER, &scheduler, false){};

    bool Callback() {
        if (defaultTZ->hour() != hour || defaultTZ->minute() != minute) {
            lcdController.setDateTime(defaultTZ->dateTime("d/m/Y").c_str(), defaultTZ->dateTime("H:i T").c_str());
            hour = defaultTZ->hour();
            minute = defaultTZ->minute();
        }
        ezt::events();
        MDNS.update();
        return true;
    }
};

UpdateTask updateTask(scheduler);
Timezone tz;

void setup() {
    // BlockingBeep bootBeep(BUZZER, 1023, 5000, 20, 60, 3); // Loud beep
    BlockingBeep bootBeep(BUZZER, 400, 2000, 20, 60, 3); // Soft beep
    bootBeep.play();

    {
        semaphore.configuring(true);

        lcdController.showBooting();

        if (button.closed()) {
            lcdController.showConnectToPortal(configManager.getPortalName());
            configManager.configure();
        }

        lcdController.showConnecting();
        if (connectionManager.connect(WIFI_TIMEOUT) != CONNECTIONMANAGER_CONNECTED) {
            lcdController.showSleeping();
            ESP.deepSleep(0);
        }

        if (!MDNS.begin(configManager.getHostname().c_str())) {
            Serial.println("Cannot start mDNS");
        }
        Serial.println("mDNS started as " + String(configManager.getHostname().c_str()));
        MDNS.addService("chanams-broker", "tcp", configManager.getListeningPort());

        ezt::waitForSync();
        Serial.print("Trying to set timezone to ");
        Serial.print(configManager.getTimezone().c_str());
        Serial.print("... ");

        if (tz.setLocation(configManager.getTimezone().c_str())) {
            Serial.println("success.");
            tz.setDefault();
        } else {
            Serial.println("failed.");
        }

        lcdController.setWifi(connectionManager.ssid());
        lcdController.setHostname(configManager.getHostname());
        lcdController.setIP(connectionManager.ip());
        lcdController.setListeningPort(configManager.getListeningPort());
        lcdController.setBatteryVccThreshold(configManager.getBatteryVccThreshold());

        lcdController.showStatus();

        semaphore.configuring(false);
    }
    {
        semaphore.waiting(true);

        broker.init();
        broker.subscribe(TOPIC_CHANAMS + String("/#"), 1);

        updateTask.enable();
        alarms.enable();
    }
}

void loop() {
    scheduler.execute();
}
