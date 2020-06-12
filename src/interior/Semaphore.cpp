#include "interior/Semaphore.h"

Semaphore::Semaphore(uint8_t redLedPin, uint8_t orangeLedPin, uint8_t greenLedPin, uint8_t buzzerPin, Scheduler &scheduler)
    : greenLed(greenLedPin, scheduler),
      orangeLed(orangeLedPin, scheduler),
      redLed(redLedPin, scheduler){};

void Semaphore::configuring(bool configuring) {
    if (configuring) {
        status = status | CONFIGURING_LIGHT;
    } else {
        status = status & ~CONFIGURING_LIGHT;
    }
    checkOrangeLed();
    checkLeds();
};

void Semaphore::waiting(bool waiting) {
    if (waiting) {
        status = status | WAITING_LIGHT;
    } else {
        status = status & ~WAITING_LIGHT;
    }
    checkLeds();
};

void Semaphore::dead(bool dead) {
    if (dead) {
        status = status | DEAD_LIGHT;
    } else {
        status = status & ~DEAD_LIGHT;
    }
    configuring(false);
    waiting(false);
    checkLeds();
};

void Semaphore::depositFull(boolean full) {
    if (full) {
        status = status | DEPOSIT_FULL_LIGHT;
        redLed.blink();
    } else {
        status = status & ~DEPOSIT_FULL_LIGHT;
    }
    configuring(false);
    waiting(false);
    dead(false);
    checkLeds();
};

void Semaphore::batteryLow(bool low) {
    if (low) {
        status = status | BATTERY_LOW_LIGHT;
    } else {
        status = status & ~BATTERY_LOW_LIGHT;
    }
    configuring(false);
    waiting(false);
    dead(false);
    checkLeds();
};

void Semaphore::checkLeds() {
    checkGreenLed();
    checkOrangeLed();
    checkRedLed();
}

void Semaphore::checkGreenLed() {
    if (status & CONFIGURING_LIGHT || status & WAITING_LIGHT || status & DEAD_LIGHT) {
        greenLed.off();
    } else if (status & BATTERY_LOW_LIGHT) {
        greenLed.blink();
    } else {
        greenLed.on();
    }
}

void Semaphore::checkOrangeLed() {
    if (status & CONFIGURING_LIGHT) {
        orangeLed.on();
    } else if (status & WAITING_LIGHT) {
        orangeLed.blink();
    } else {
        orangeLed.off();
    }
}

void Semaphore::checkRedLed() {
    if (status & DEAD_LIGHT) {
        redLed.on();
    } else if (status & DEPOSIT_FULL_LIGHT) {
        redLed.blink();
    } else {
        redLed.off();
    }
}
