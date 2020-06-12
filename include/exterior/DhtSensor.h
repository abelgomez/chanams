#pragma once

#include <Arduino.h>

class DhtSensor {

public:
	typedef struct {
		float temperature;
		float humidity;
		float heatIndex;
	} dht_data;

	DhtSensor(uint8_t sensorPin, uint8_t powerPin, bool doPower);
	void powerOn();
	void powerOff();
	dht_data read();
	virtual ~DhtSensor();
private:
	uint8_t sensorPin;
	uint8_t powerPin;
	bool doPower;
};
