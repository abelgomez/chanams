#include <Arduino.h>

#include <ESP8266mDNS.h>

#include "ConnectionManager.h"
#include "exterior/Sensors.h"
#include "exterior/ExteriorConfigManager.h"
#include "exterior/MqttManager.h"

#define WIFI_TIMEOUT 7000

void setup() {
	Serial.begin(9600);
	Serial.println("");

	Sensors sensors;
	ExteriorConfigManager configManager;
	if (sensors.configButtonPressed()) {
		configManager.configure();
	}

	ConnectionManager connectionManager;
	if (connectionManager.connect(WIFI_TIMEOUT) != CONNECTIONMANAGER_CONNECTED) {
        ESP.deepSleep(0);
	}

    if (!MDNS.begin(configManager.getHostname().c_str())) {
        Serial.println("Cannot start mDNS");
    }
    Serial.println("mDNS started as " + String(configManager.getHostname().c_str()));

	MqttManager mqttManager(configManager.getBroker(), configManager.getBrokerPort());
	mqttManager.publish(sensors);

	Serial.printf("Now sleeping for %d minutes.\n", configManager.getUpdateTimeMinutes());
	ESP.deepSleep(configManager.getUpdateTimeMicroSeconds());
}

void loop() {
}
