#include "ConnectionManager.h"

#include <ESP8266WiFi.h>

int ConnectionManager::connect(uint timeout) {
    Serial.print("Attempting wifi connection...");
    WiFi.begin();
    uint waited = 0;
    while (WiFi.status() != WL_CONNECTED && waited < timeout) {
        waited += 500;
        delay(500);
        Serial.print(".");
    }
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println(" failed.");
        if (waited >= timeout) {
            return CONNECTIONMANAGER_ERR_TIMEOUT;
        } else {
            return CONNECTIONMANAGER_ERR_FAILED;
        }
    } else {
        Serial.println(" connected.");
        Serial.print("Connected to ");
        Serial.println(WiFi.SSID());
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
        return CONNECTIONMANAGER_CONNECTED;
    }
}

std::string ConnectionManager::ssid() {
    return WiFi.SSID().c_str();
}

std::string ConnectionManager::ip() {
    return WiFi.localIP().toString().c_str();
}