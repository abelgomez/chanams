#include <Arduino.h>

#include <ESP8266mDNS.h>

#include "ConnectionManager.h"
#include "exterior/ExteriorConfigManager.h"
#include "exterior/MqttManager.h"
#include "exterior/Sensors.h"

#define WIFI_TIMEOUT 15000
#define WIFI_RETRIES 3

void setup() {
    Serial.begin(9600);
    Serial.println("");

    Sensors sensors;
    ExteriorConfigManager configManager;
    if (sensors.configButtonPressed()) {
        configManager.configure();
    }

    ConnectionManager connectionManager;
    Serial.println("Connecting to WiFi...");
    for (int retries = WIFI_RETRIES; retries > 0; retries--) {
        Serial.print(retries);
        Serial.println(" retries left...");
        int result = connectionManager.connect(WIFI_TIMEOUT);
        if (result == CONNECTIONMANAGER_ERR_TIMEOUT) {
            continue;
        } else if (result == CONNECTIONMANAGER_CONNECTED) {
            if (!MDNS.begin(configManager.getHostname().c_str())) {
                Serial.println("Cannot start mDNS");
            }
            Serial.println("mDNS started as " + String(configManager.getHostname().c_str()));

            MqttManager mqttManager(configManager.getBroker(), configManager.getBrokerPort());
            mqttManager.publish(sensors);
            break;
        }
    }

    Serial.printf("Now sleeping for %d minutes.\n", configManager.getUpdateTimeMinutes());
    ESP.deepSleep(configManager.getUpdateTimeMicroSeconds());
}

void loop() {
}
