#include "exterior/ExteriorConfigManager.h"

#include <FS.h>

#define HOSTNAME_KEY "hostname"
#define UPDATE_TIME_KEY "updateTime"
#define BROKER_KEY "broker"
#define BROKER_PORT_KEY "brokerPort"

ExteriorConfigManager::ExteriorConfigManager() {
    load();
    hostnameParam = new WiFiManagerParameter(HOSTNAME_KEY, "Nombre de host", this->getHostname().c_str(), 32);
    brokerParam = new WiFiManagerParameter(BROKER_KEY, "Nombre o IP del host interior", this->getBroker().c_str(), 127);
    brokerPortParam = new WiFiManagerParameter(BROKER_PORT_KEY, "Puerto de escucha del host interior", String(this->getBrokerPort()).c_str(), 5);
    updateTimeParam = new WiFiManagerParameter(UPDATE_TIME_KEY, "Tiempo de espera entre mensajes (minutos)", String(this->getUpdateTimeMinutes()).c_str(), 2);
}

ExteriorConfigManager::~ExteriorConfigManager() {
    delete hostnameParam;
    delete brokerParam;
    delete brokerPortParam;
    delete updateTimeParam;
}

void ExteriorConfigManager::readJson(DynamicJsonDocument &doc) {
    hostname = doc[HOSTNAME_KEY] | DEFAULT_EXTERIOR_NAME;
    updateTimeMinutes = doc[UPDATE_TIME_KEY] | DEFAULT_TIME_BETWEN_UPDATES;
    broker = doc[BROKER_KEY] | DEFAULT_INTERIOR_FQN;
    brokerPort = doc[BROKER_PORT_KEY] | DEFAULT_LISTENING_PORT;
    Serial.println("Loaded config:");
    Serial.print("hostname: ");
    Serial.println(hostname.c_str());
    Serial.print("broker: ");
    Serial.println(broker.c_str());
    Serial.print("brokerPort: ");
    Serial.println(brokerPort);
    Serial.print("updateTimeMinutes: ");
    Serial.println(updateTimeMinutes);
}

void ExteriorConfigManager::writeJson(DynamicJsonDocument &doc) {
    doc[HOSTNAME_KEY] = hostname;
    doc[BROKER_KEY] = broker;
    doc[BROKER_PORT_KEY] = brokerPort;
    doc[UPDATE_TIME_KEY] = updateTimeMinutes;
};

std::string ExteriorConfigManager::getPortalName() {
    return EXTERIOR_CONFIG_PORTAL_NAME;
}

std::string ExteriorConfigManager::getHostname() {
    return this->hostname;
}

void ExteriorConfigManager::setHostname(std::string hostname) {
    this->hostname = hostname;
}

std::string ExteriorConfigManager::getBroker() {
    return this->broker;
}

void ExteriorConfigManager::setBroker(std::string broker) {
    this->broker = broker;
}

uint ExteriorConfigManager::getBrokerPort() {
    return this->brokerPort;
}

void ExteriorConfigManager::setBrokerPort(uint brokerPort) {
    this->brokerPort = brokerPort;
}

void ExteriorConfigManager::setBrokerPort(std::string brokerPort) {
    this->brokerPort = std::atoi(brokerPort.c_str());
}

uint ExteriorConfigManager::getUpdateTimeMinutes() {
    return this->updateTimeMinutes;
}

ulong ExteriorConfigManager::getUpdateTimeMicroSeconds() {
    return this->getUpdateTimeMinutes() * 60e6;
}

void ExteriorConfigManager::setUpdateTimeMinutes(ulong updateTimeMinutes) {
    this->updateTimeMinutes = updateTimeMinutes;
}

void ExteriorConfigManager::setUpdateTimeMinutes(std::string updateTimeMinutes) {
    this->updateTimeMinutes = std::atoi(updateTimeMinutes.c_str());
}

void ExteriorConfigManager::addParameters(WiFiManager &manager) {
    manager.addParameter(hostnameParam);
    manager.addParameter(brokerParam);
    manager.addParameter(brokerPortParam);
    manager.addParameter(updateTimeParam);
}

void ExteriorConfigManager::retrieveParameters() {
    setHostname(hostnameParam->getValue());
    setBroker(brokerParam->getValue());
    setBrokerPort(brokerPortParam->getValue());
    setUpdateTimeMinutes(updateTimeParam->getValue());
}
