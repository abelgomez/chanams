#include "interior/LedController.h"

Led::Led(uint8_t pin) : pin(pin) {
    off();
};

void Led::on() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
}

void Led::off() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
}

void Led::invert() {
    pinMode(pin, OUTPUT);
    digitalWrite(pin, !digitalRead(pin));
}

LedController::LedController(uint8_t pin, Scheduler &scheduler)
    : Task(500, TASK_FOREVER, &scheduler, false), led(pin) {
    count = 0;
}

void LedController::on() {
    if (this->isEnabled()) {
        this->disable();
    }
    led.on();
}

void LedController::off() {
    if (this->isEnabled()) {
        this->disable();
    }
    led.off();
}

void LedController::blink() {
    if (!this->isEnabled()) {
        this->enable();
    }
}

bool LedController::Callback() {
    if (count == 0) {
        led.on();
    } else {
        led.off();
    }
    count = (count + 1) % 3;
    return false;
}
