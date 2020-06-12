#include "exterior/DhtSensor.h"

#include <DHT.h>
#include <SPI.h>

#define MAX_ATTEMPTS 8

DhtSensor::DhtSensor(uint8_t sensorPin, uint8_t powerPin, bool doPower) : sensorPin(sensorPin), powerPin(powerPin), doPower(doPower) {
	// Power the sensor on to save initialization time
	if (doPower) {
		powerOn();
	}
}

void DhtSensor::powerOn() {
	pinMode(powerPin, OUTPUT);
	digitalWrite(powerPin, HIGH);
}

void DhtSensor::powerOff() {
	digitalWrite(powerPin, LOW);
}

DhtSensor::dht_data DhtSensor::read() {
	dht_data data;

	// Make sure the sensor is powered on
	powerOn();

	DHT dht(sensorPin, DHT22);
	dht.begin();

	int attempt = 1;
	do {
		if (attempt > 1) {
			delay(500);
		}
		Serial.printf("Reading DHT22 attempt (%d/%d)\n", attempt, MAX_ATTEMPTS);
		data.temperature = dht.readTemperature();
		data.humidity = dht.readHumidity();
		data.heatIndex = dht.computeHeatIndex(data.temperature, data.humidity, false);
		attempt++;
	} while (attempt <= MAX_ATTEMPTS && (isnan(data.temperature) || isnan(data.humidity) || isnan(data.heatIndex)));

	// The app running this code will call deepSleep
	// Power the sensor off asuming that the destructor
	// won't be called before sleeping
	powerOff();

	return data;
}

DhtSensor::~DhtSensor() {
	powerOff();
}

