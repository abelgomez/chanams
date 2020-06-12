#pragma once

#include <Arduino.h>
#include "DhtSensor.h"

class Sensors {

public:
	float batteryVoltage();
	bool depositFull();
	bool configButtonPressed();
	float temperature();
	float humidity();
	float heatIndex();

private:
	DhtSensor::dht_data cachedData;
	unsigned long lastRead;
	DhtSensor::dht_data getData();
};
