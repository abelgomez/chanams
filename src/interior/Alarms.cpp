#include "interior/Alarms.h"

Alarms::Alarms(uint8_t buzzerPin, Switch &button, InteriorConfigManager &configManager, Scheduler &scheduler)
    : Task(200, TASK_FOREVER, &scheduler, false),
      button(button),
      depositAlarm(buzzerPin, scheduler, 50, 1, 500, 1000),
      deadAlarm(buzzerPin, scheduler, 50),
      batteryLowBeep(buzzerPin, 800, 3000, 50, 80, 1),
      configManager(configManager){};

void Alarms::dead(bool dead) {
    if (dead) {
        status = status | DEAD_ALARM;
    } else {
        status = status & ~DEAD_ALARM;
    }
    deadAlarm.stop();
};

void Alarms::depositFull(bool full) {
    if (full) {
        status = status | DEPOSIT_FULL_ALARM;
    } else {
        status = status & ~DEPOSIT_FULL_ALARM;
    }
    depositAlarm.stop();
};

void Alarms::batteryLow(bool low) {
    if (low) {
        status = status | BATTERY_LOW_ALARM;
    } else {
        status = status & ~BATTERY_LOW_ALARM;
    }
};

void Alarms::allOff() {
    depositAlarm.silence();
    deadAlarm.silence();
}

bool Alarms::Callback() {
    static int lastHour = -1;
    if (button.closed() || status & NO_ALARM) {
        allOff();
        status = NO_ALARM; // Set this here to avoid enabling alarms in the next loop
    } else {
        uint now = defaultTZ->hour() * 60 + defaultTZ->minute();
        uint startQuiet = configManager.getStartQuietHours() * 60 + configManager.getStartQuietMinutes();
        uint endQuiet = configManager.getEndQuietHours() * 60 + configManager.getEndQuietMinutes();
        if (startQuiet <= endQuiet && startQuiet <= now && now < endQuiet) {
            allOff();
        } else if (startQuiet > endQuiet && (startQuiet <= now || now < endQuiet)) {
            allOff();
        } else if (status & DEAD_ALARM) {
            if (!deadAlarm.isActive()) {
                allOff();
                deadAlarm.play();
            }
        } else if (status & DEPOSIT_FULL_ALARM) {
            if (!depositAlarm.isActive()) {
                allOff();
                depositAlarm.play(60);
            }
        } else if (status & BATTERY_LOW_ALARM) {
            if (lastHour != defaultTZ->hour()) {
                lastHour = defaultTZ->hour();
                batteryLowBeep.play();
            }
        } else {
            allOff();
        }
    }
    return true;
}