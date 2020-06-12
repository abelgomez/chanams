#include "interior/Beepers.h"

Beep1::Beep1(uint8_t pin, Scheduler &scheduler, int volume, uint32_t frequency, ulong tsound, ulong tsilence)
    : Task(0, TASK_FOREVER, &scheduler, false), pin(pin), volume(volume), frequency(frequency), tsound(tsound), tsilence(tsilence) {
    pinMode(pin, OUTPUT);
}

void Beep1::play() {
    this->enable();
}

void Beep1::play(int seconds) {
    Serial.print("Iterations ");
    this->setIterations((2 * seconds) / ((float)(tsound + tsilence) / 1000));
    this->enable();
}

boolean Beep1::playing() {
    return this->isEnabled();
}

void Beep1::stop() {
    this->disable();
}

boolean Beep1::OnEnable() {
    it = 0;
    return true;
}

void Beep1::OnDisable() {
    noTone(pin);
}

bool Beep1::Callback() {
    if (it % 2 == 0) {
        analogWriteFreq(frequency);
        analogWrite(pin, volume);
        delay(tsound);
    } else if (it % 2 == 1) {
        noTone(pin);
        delay(tsilence);
    }
    it = (it + 1) % 2;
    if (isLastIteration()) {
        noTone(pin);
    }
    return false;
}

Beep2::Beep2(uint8_t pin, Scheduler &scheduler, int volume)
    : Task(0, TASK_FOREVER, &scheduler, false), pin(pin), volume(volume) {
    pinMode(pin, OUTPUT);
}

void Beep2::play() {
    this->enable();
}

void Beep2::play(int seconds) {
    this->setIterations((3 * seconds) / 2);
    this->enable();
}

boolean Beep2::playing() {
    return this->isEnabled();
}

void Beep2::stop() {
    this->disable();
}

boolean Beep2::OnEnable() {
    it = 0;
    return true;
}

void Beep2::OnDisable() {
    noTone(pin);
}

bool Beep2::Callback() {
    if (it % 3 == 0) {
        analogWriteFreq(523);
        analogWrite(pin, volume);
        delay(500);
    } else if (it % 3 == 1) {
        analogWriteFreq(445);
        analogWrite(pin, volume);
        delay(1000);
    } else if (it % 3 == 2) {
        noTone(pin);
        delay(500);
    }
    it = (it + 1) % 3;
    if (isLastIteration()) {
        noTone(pin);
    }
    return true;
}

BlockingBeep::BlockingBeep(uint8_t pin, int volume, uint32_t frequency, ulong tsound, ulong tsilence, uint numBeeps)
    : pin(pin), volume(volume), frequency(frequency), tsound(tsound), tsilence(tsilence), numBeeps(numBeeps) {}

void BlockingBeep::play() {
    pinMode(pin, OUTPUT);
    for (uint i = 0; i < numBeeps; i++) {
        analogWriteFreq(frequency);
        analogWrite(pin, volume);
        delay(tsound);
        noTone(pin);
        delay(tsilence);
    }
}
