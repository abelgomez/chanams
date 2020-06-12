#pragma once

#include <Arduino.h>
#include "ConfigManager.h"
#include "GlobalConstants.h"

class ExteriorConfigManager : public ConfigManager {
public:
    ExteriorConfigManager();
    ~ExteriorConfigManager();

    std::string getPortalName();
    std::string getHostname();
    uint getUpdateTimeMinutes();
    ulong getUpdateTimeMicroSeconds();
    std::string getBroker();
    uint getBrokerPort();

private:
    std::string hostname = DEFAULT_EXTERIOR_NAME;
    std::string broker = DEFAULT_INTERIOR_FQN;
    uint brokerPort = DEFAULT_LISTENING_PORT;
    uint updateTimeMinutes = DEFAULT_TIME_BETWEN_UPDATES;

    WiFiManagerParameter *hostnameParam;
    WiFiManagerParameter *brokerParam;
    WiFiManagerParameter *brokerPortParam;
    WiFiManagerParameter *updateTimeParam;

    virtual void readJson(DynamicJsonDocument &doc);
    virtual void writeJson(DynamicJsonDocument &doc);
    virtual void addParameters(WiFiManager &manager);
    virtual void retrieveParameters();

    void setHostname(std::string updateTimeMinutes);
    void setUpdateTimeMinutes(ulong updateTimeMinutes);
    void setUpdateTimeMinutes(std::string updateTimeMinutes);
    void setBroker(std::string broker);
    void setBrokerPort(uint brokerPort);
    void setBrokerPort(std::string brokerPort);
};
