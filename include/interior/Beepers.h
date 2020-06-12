#pragma once

#define _TASK_OO_CALLBACKS

#include <Arduino.h>
#include <TaskSchedulerDeclarations.h>

class Beep1 : public Task {
public:
    Beep1(uint8_t pin, Scheduler &scheduler, int volume, uint32_t frequency, ulong tsound, ulong tsilence);

    void play();
    void play(int seconds);
    boolean playing();
    void stop();
    virtual boolean OnEnable();
    virtual void OnDisable();
    bool Callback();

private:
    uint8_t pin;
    uint it = 0;
    int volume;
    uint32_t frequency;
    ulong tsound;
    ulong tsilence;
};

class Beep2 : public Task {
public:
    Beep2(uint8_t pin, Scheduler &scheduler, int volume);

    void play();
    void play(int seconds);
    boolean playing();
    void stop();
    virtual boolean OnEnable();
    virtual void OnDisable();
    bool Callback();

private:
    uint8_t pin;
    uint it = 0;
    int volume;
};

class BlockingBeep {
public:
    BlockingBeep(uint8_t pin, int volume, uint32_t frequency, ulong tsound, ulong tsilence, uint numBeeps);

    void play();

private:
    uint8_t pin;
    int volume;
    uint32_t frequency;
    ulong tsound;
    ulong tsilence;
    uint numBeeps;
};
