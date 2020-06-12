#pragma once

#define _TASK_OO_CALLBACKS

#include "Switch.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <TaskSchedulerDeclarations.h>
#include <Wire.h>
#include "GlobalConstants.h"

enum DepositState {
    DEPOSIT_EMPTY = 0,
    DEPOSIT_FULL = 1,
    DEPOSIT_UNKNOWN = -1
};

class LcdController;

class DisableDisplayTimer : public Task {
public:
    DisableDisplayTimer(unsigned long timeoutSeconds, LcdController *controller, Scheduler &scheduler);
    void restore();
    bool Callback();

private:
    LcdController *controller;
};

class ShowHomeScreenTimer : public Task {
public:
    ShowHomeScreenTimer(unsigned long timeoutSeconds, LcdController *controller, Scheduler &scheduler);
    void restore();
    bool Callback();

private:
    LcdController *controller;
};

class LcdController : public Task {
public:
    LcdController(uint8_t sdaPin, uint8_t sclPin, Switch &button, Scheduler &scheduler);

    void setTemperature(float temperature);
    void setHumidity(float humidity);
    void setDepositFull(boolean full);
    void setBatteryVccThreshold(float batteryVcc);
    void setBatteryVcc(float batteryVcc);
    void setWifi(std::string wifi);
    void setIP(std::string ip);
    void setHostname(std::string hostname);
    void setListeningPort(uint listeningPort);
    void setDateTime(std::string date, std::string time);

    void showBooting();
    void showConnectToPortal(std::string portalName);
    void showConnecting();
    void showSleeping();
    void showDeadAlarm();
    void showStatus();
    bool Callback();

private:
    LiquidCrystal_I2C lcd;
    Switch button;

    float temperature = nanf("");
    float humidity = nanf("");
    DepositState depositFull = DEPOSIT_UNKNOWN;
    float batteryVccThreshold = DEFAULT_BATTERY_VCC_THRESHOLD;
    float batteryVcc = nanf("");
    std::string wifi = "<sin wifi>";
    std::string hostname = "<sin nombre>";
    std::string ip = "0.0.0.0";
    uint listeningPort = -1;
    std::string date = "<sin fecha>";
    std::string time = "<sin hora>";

    DisableDisplayTimer disableDisplayTimer;
    ShowHomeScreenTimer showHomeScreenTimer;
    int currentScreen = 0;
    boolean buttonWasPressed = false;

    void show(std::string line1);
    void show(std::string line1, std::string line2);
    void showScreen(int screen);
    void showScreen(int screen, boolean silent);
    std::string toOneDecimal(float value);
    void backlight();
    void noBacklight();
    friend class DisableDisplayTimer;
    friend class ShowHomeScreenTimer;
};
