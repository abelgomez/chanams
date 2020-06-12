#pragma once

#define _TASK_OO_CALLBACKS

#include "Switch.h"
#include "interior/Beepers.h"
#include "interior/InteriorConfigManager.h"
#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>


enum AlarmStatus {
    NO_ALARM = 0,
    BATTERY_LOW_ALARM = 1 << 0,
    DEPOSIT_FULL_ALARM = 1 << 1,
    DEAD_ALARM = 1 << 2
};


class Alarms : public Task {
public:
    Alarms(uint8_t buzzerPin, Switch &button, InteriorConfigManager &configManager, Scheduler &scheduler);

    void dead(bool dead);
    void depositFull(bool full);
    void batteryLow(bool low);

    bool Callback();

private:
    Switch button;
    Beep1 depositAlarm;
    Beep2 deadAlarm;
    BlockingBeep batteryLowBeep;
    InteriorConfigManager configManager;
    uint status = NO_ALARM;

    void allOff();
};
