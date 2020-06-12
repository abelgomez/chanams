#pragma once

#define _TASK_OO_CALLBACKS

#include "LedController.h"
#include "Switch.h"
#include "interior/Beepers.h"
#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>

enum SemaphoreStatus {
    NORMAL_LIGHT       = 0,       // GREEN ON
    BATTERY_LOW_LIGHT  = 1 << 0,  // GREEN BLINK
    CONFIGURING_LIGHT  = 1 << 1,  // ORANGE ON
    WAITING_LIGHT      = 1 << 2,  // ORANGE BLINK
    DEAD_LIGHT         = 1 << 3,  // RED ON
    DEPOSIT_FULL_LIGHT = 1 << 4,  // RED BLINK
};

class Semaphore {
public:
    Semaphore(uint8_t redLedPin, uint8_t orangeLedPin, uint8_t greenLedPin, uint8_t buzzerPin, Scheduler &scheduler);

    void configuring(bool configuring = true);
    void waiting(bool waiting = true);
    void dead(bool dead);
    void depositFull(bool full);
    void batteryLow(bool low);

private:
    LedController greenLed;
    LedController orangeLed;
    LedController redLed;

    uint status;

    void checkLeds();
    void checkGreenLed();
    void checkOrangeLed();
    void checkRedLed();
    void allOff();
};
