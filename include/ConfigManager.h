#pragma once

#include <Arduino.h>
#define ARDUINOJSON_ENABLE_STD_STRING 1
#include <ArduinoJson.h>
#include <WifiManager.h>

class ConfigManager {
public:
    virtual std::string getPortalName() = 0;
    void configure();

private:
    void formatFS();
    
protected:
    void load();
    void save();
    virtual void readJson(DynamicJsonDocument &doc) = 0;
    virtual void writeJson(DynamicJsonDocument &doc) = 0;
    virtual void addParameters(WiFiManager &manager) = 0;
    virtual void retrieveParameters() = 0;
};
