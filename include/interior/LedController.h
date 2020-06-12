#pragma once

#define _TASK_OO_CALLBACKS

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>

class Led {
public:
    Led(uint8_t pin);

    void on();
    void off();
    void invert();

private:
    uint8_t pin;
};


class LedController : public Task {
public:
    LedController(uint8_t pin, Scheduler &scheduler);

    void on();
    void off();
    void blink();
    bool Callback();

private:
    Led led;
    int count;
};
