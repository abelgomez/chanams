#include "exterior/Sensors.h"

#include "Switch.h"
#include "exterior/DhtSensor.h"

#define DEPOSIT_SWITCH D1
#define CONFIG_SWITCH D7
#define DHT_SENSOR D5
#define DHT_SENSOR_POWER D6
#define POWER_SENSOR A0

DhtSensor dht22(DHT_SENSOR, DHT_SENSOR_POWER, true);
Switch configSwitch(CONFIG_SWITCH);
Switch depositSwitch(DEPOSIT_SWITCH);

float Sensors::batteryVoltage() {
	// This function is designed to calculate the input voltage
	// of the battery considering a max voltage of 6.4 volts
	// That implies that a resistor of 320k ohm must be placed
	// between Vin and A0 pin (which will increase the resistance
	// of the already existing voltage divider). Se also
	// https://www.letscontrolit.com/wiki/index.php/DC_Voltage_divider
	float sensorValue = analogRead(POWER_SENSOR);
	// Convert the value from 0 to 1023 (0 = 0v in ESP chip;
	// 1023 = 1v in ESP chip) to 0 to 6.4v
	return sensorValue * (6.4f / 1023.0f);
}

bool Sensors::depositFull() {
	return depositSwitch.open();
}

bool Sensors::configButtonPressed() {
	return configSwitch.closed();
}

float Sensors::temperature() {
	return getData().temperature;
}

float Sensors::humidity() {
	return getData().humidity;
}

float Sensors::heatIndex() {
	return getData().heatIndex;
}

DhtSensor::dht_data Sensors::getData() {
	unsigned long now = millis();
	if (now - lastRead > 1000) {
		cachedData = dht22.read();
		lastRead = now;
	}
	return cachedData;
}