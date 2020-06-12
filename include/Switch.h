#pragma once
#include <Arduino.h>

class Switch {
public:
    Switch(uint8_t pin);

    bool open();
    bool closed();

private:
    uint8_t pin;
};
