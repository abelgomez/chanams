#pragma once

#include <Arduino.h>
#include <ezTime.h>
#include "ConfigManager.h"
#include "GlobalConstants.h"

class InteriorConfigManager : public ConfigManager {
public:
    InteriorConfigManager();
    ~InteriorConfigManager();
    
    std::string getPortalName();
    std::string getHostname();
    uint getListeningPort();
    uint getTimeoutMinutes();
    float getBatteryVccThreshold();
    std::string getTimezone();
    uint getStartQuietHours();
    uint getStartQuietMinutes();
    uint getEndQuietHours();
    uint getEndQuietMinutes();


private:
    std::string hostname = DEFAULT_INTERIOR_NAME;
    uint listeningPort = DEFAULT_LISTENING_PORT;
    uint timeoutMinutes = DEFAULT_TIMEOUT;
    float batteryVccThreshold = DEFAULT_BATTERY_VCC_THRESHOLD;
    std::string timezone = DEFAULT_TIMEZONE;
    uint startQuietHours = DEFAULT_START_QUIET_HOURS;
    uint startQuietMinutes = DEFAULT_START_QUIET_MINUTES;
    uint endQuietHours = DEFAULT_END_QUIET_HOURS;
    uint endQuietMinutes = DEFAULT_END_QUIET_MINUTES;

    WiFiManagerParameter *hostnameParam;
    WiFiManagerParameter *listeningPortParam;
    WiFiManagerParameter *timeoutParam;
    WiFiManagerParameter *batteryVccThresholdParam;
    WiFiManagerParameter *timezoneParam;
    WiFiManagerParameter *startQuietHoursParam;
    WiFiManagerParameter *startQuietMinutesParam;
    WiFiManagerParameter *endQuietHoursParam;
    WiFiManagerParameter *endQuietMinutesParam;

    virtual void readJson(DynamicJsonDocument &doc);
    virtual void writeJson(DynamicJsonDocument &doc);
    virtual void addParameters(WiFiManager &manager);
    virtual void retrieveParameters();

    void setHostname(std::string updateTimeMinutes);
    void setListeningPort(uint brokerPort);
    void setListeningPort(std::string brokerPort);
    void setTimeoutMinutes(ulong updateTimeMinutes);
    void setTimeoutMinutes(std::string updateTimeMinutes);
    void setBatteryVccThreshold(float batteryVccThreshold);
    void setBatteryVccThreshold(std::string batteryVccThreshold);
    void setTimezone(std::string timezone);
    void setStartQuietHours(uint startQuietHours);
    void setStartQuietHours(std::string startQuietHours);
    void setStartQuietMinutes(uint startQuietMinutes);
    void setStartQuietMinutes(std::string startQuietMinutes);
    void setEndQuietHours(uint endQuietHours);
    void setEndQuietHours(std::string endQuietHours);
    void setEndQuietMinutes(uint endQuietMinutes);
    void setEndQuietMinutes(std::string endQuietMinutes);
};
