#include "Switch.h"

Switch::Switch(uint8_t pin) : pin(pin) {
    pinMode(pin, INPUT_PULLUP);
};

bool Switch::open() {
    return digitalRead(pin) == HIGH;
}

bool Switch::closed() {
    return !open();
}
