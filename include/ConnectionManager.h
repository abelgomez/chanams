#pragma once

#include <Arduino.h>

#define CONNECTIONMANAGER_CONNECTED 0
#define CONNECTIONMANAGER_ERR_TIMEOUT 1
#define CONNECTIONMANAGER_ERR_FAILED 2

class ConnectionManager {
public:
    int connect(uint timeout);
    std::string ssid();
    std::string ip();
};
