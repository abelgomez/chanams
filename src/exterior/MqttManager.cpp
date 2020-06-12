#include "exterior/MqttManager.h"

#include <WiFiClient.h>
// Redefine MQTT_SOCKET_TIMEOUT in PubSubClient to avoid a bigger battery drain in case the broker is not available
#define MQTT_SOCKET_TIMEOUT 5
#include <PubSubClient.h>

#define MAX_ATTEMPTS 8


MqttManager::MqttManager(std::string broker, uint brokerPort) : broker(broker), brokerPort(brokerPort) {};

void MqttManager::publish(Sensors sensors) {
	WiFiClient wifiClient;
	PubSubClient client(wifiClient);
	Serial.print("Creating MQTT connection to ");
	Serial.print(broker.c_str());
	Serial.print(":");
	Serial.print(brokerPort);
	Serial.print("... ");
	client.setServer(broker.c_str(), brokerPort);
	if (!client.connect(DEFAULT_EXTERIOR_NAME)) {
		Serial.println("failed.");
	} else {
		Serial.println("success.");
		Serial.println("Publishing...");
		Serial.printf("%s = %s\n", TOPIC_CHANAMS_DEPOSIT, sensors.depositFull() ? "true" : "false");
		Serial.printf("%s = %s\n", TOPIC_CHANAMS_VCC, String(sensors.batteryVoltage()).c_str());
		Serial.printf("%s = %s\n", TOPIC_CHANAMS_TEMPERATURE, String(sensors.temperature()).c_str());
		Serial.printf("%s = %s\n", TOPIC_CHANAMS_HUMIDITY, String(sensors.humidity()).c_str());
		Serial.printf("%s = %s\n", TOPIC_CHANAMS_HEAT_INDEX, String(sensors.heatIndex()).c_str());
		client.publish(TOPIC_CHANAMS_DEPOSIT, sensors.depositFull() ? "true" : "false", true);
		client.publish(TOPIC_CHANAMS_VCC, String(sensors.batteryVoltage()).c_str(), true);
		client.publish(TOPIC_CHANAMS_TEMPERATURE, String(sensors.temperature()).c_str(), true);
		client.publish(TOPIC_CHANAMS_HUMIDITY, String(sensors.humidity()).c_str(), true);
		client.publish(TOPIC_CHANAMS_HEAT_INDEX, String(sensors.heatIndex()).c_str(), true);
		Serial.print("Disconnecting... ");
		client.disconnect();
		Serial.println("disconnected.");
	}
}

