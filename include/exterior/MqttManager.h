#pragma once

#include <Arduino.h>
#include "Sensors.h"
#include "GlobalConstants.h"

class MqttManager {

public:
	MqttManager(std::string broker, uint brokerPort);
	void publish(Sensors sensors);
	
private:
	std::string broker;
	uint brokerPort;
};
