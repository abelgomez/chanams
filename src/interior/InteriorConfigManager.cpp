#include "interior/InteriorConfigManager.h"

#include <FS.h>

#define HOSTNAME_KEY "hostname"
#define TIMEOUT_KEY "timeout"
#define LISTENING_PORT_KEY "listeningPort"
#define BATTERY_VCC_THRESHOLD_KEY "batteryVccThreshold"
#define TIMEZONE_KEY "timezone"
#define START_QUIET_HOURS_KEY "startQuietHours"
#define START_QUIET_MINUTES_KEY "startQuietMinutes"
#define END_QUIET_HOURS_KEY "endQuietHours"
#define END_QUIET_MINUTES_KEY "endQuietMinutes"

InteriorConfigManager::InteriorConfigManager() {
    load();
    hostnameParam = new WiFiManagerParameter(HOSTNAME_KEY, "Nombre de host", this->getHostname().c_str(), 32);
    listeningPortParam = new WiFiManagerParameter(LISTENING_PORT_KEY, "Puerto de escucha", String(this->getListeningPort()).c_str(), 5);
    timeoutParam = new WiFiManagerParameter(TIMEOUT_KEY, "Tiempo de espera máximo (minutos)", String(this->getTimeoutMinutes()).c_str(), 2);
    batteryVccThresholdParam = new WiFiManagerParameter(BATTERY_VCC_THRESHOLD_KEY, "Umbral de batería baja (voltios)", String(this->getBatteryVccThreshold()).c_str(), 4);
    timezoneParam = new WiFiManagerParameter(TIMEZONE_KEY, "Zona horaria", this->getTimezone().c_str(), 32);
    startQuietHoursParam = new WiFiManagerParameter(START_QUIET_HOURS_KEY, "Inicio del periodo de silencio (hora)", String(this->getStartQuietHours()).c_str(), 2);
    startQuietMinutesParam = new WiFiManagerParameter(START_QUIET_MINUTES_KEY, "Inicio del periodo de silencio (minutos)", String(this->getStartQuietMinutes()).c_str(), 2);
    endQuietHoursParam = new WiFiManagerParameter(END_QUIET_HOURS_KEY, "Fin del periodo de silencio (hora)", String(this->getEndQuietHours()).c_str(), 2);
    endQuietMinutesParam = new WiFiManagerParameter(END_QUIET_MINUTES_KEY, "Fin del periodo de silencio (minutos)", String(this->getEndQuietMinutes()).c_str(), 2);
}

InteriorConfigManager::~InteriorConfigManager() {
    delete hostnameParam;
    delete timeoutParam;
    delete listeningPortParam;
    delete batteryVccThresholdParam;
    delete timezoneParam;
    delete startQuietHoursParam;
    delete startQuietMinutesParam;
    delete endQuietHoursParam;
    delete endQuietMinutesParam;

}

void InteriorConfigManager::readJson(DynamicJsonDocument &doc) {
    hostname = doc[HOSTNAME_KEY] | DEFAULT_INTERIOR_NAME;
    listeningPort = doc[LISTENING_PORT_KEY] | DEFAULT_LISTENING_PORT;
    timeoutMinutes = doc[TIMEOUT_KEY] | DEFAULT_TIMEOUT;
    batteryVccThreshold = doc[BATTERY_VCC_THRESHOLD_KEY] | DEFAULT_BATTERY_VCC_THRESHOLD;
    timezone = doc[TIMEZONE_KEY] | DEFAULT_TIMEZONE;
    startQuietHours = doc[START_QUIET_HOURS_KEY] | DEFAULT_START_QUIET_HOURS;
    startQuietMinutes = doc[START_QUIET_MINUTES_KEY] | DEFAULT_START_QUIET_MINUTES;
    endQuietHours = doc[END_QUIET_HOURS_KEY] | DEFAULT_END_QUIET_HOURS;
    endQuietMinutes = doc[END_QUIET_MINUTES_KEY] | DEFAULT_END_QUIET_MINUTES;
    Serial.println("Loaded config:");
    Serial.print("hostname: ");
    Serial.println(hostname.c_str());
    Serial.print("timeoutMinutes: ");
    Serial.println(timeoutMinutes);
    Serial.print("listeningPort: ");
    Serial.println(listeningPort);
    Serial.print("batteryVccThreshold: ");
    Serial.println(batteryVccThreshold);
    Serial.print("timezone: ");
    Serial.println(timezone.c_str());
    Serial.print("startQuietHours: ");
    Serial.println(startQuietHours);
    Serial.print("startQuietMinutes: ");
    Serial.println(startQuietMinutes);
    Serial.print("endQuietHours: ");
    Serial.println(endQuietHours);
    Serial.print("endQuietMinutes: ");
    Serial.println(endQuietMinutes);
};

void InteriorConfigManager::writeJson(DynamicJsonDocument &doc) {
    doc[HOSTNAME_KEY] = hostname;
    doc[LISTENING_PORT_KEY] = listeningPort;
    doc[TIMEOUT_KEY] = timeoutMinutes;
    doc[BATTERY_VCC_THRESHOLD_KEY] = batteryVccThreshold;
    doc[TIMEZONE_KEY] = timezone;
    doc[START_QUIET_HOURS_KEY] = startQuietHours;
    doc[START_QUIET_MINUTES_KEY] = startQuietMinutes;
    doc[END_QUIET_HOURS_KEY] = endQuietHours;
    doc[END_QUIET_MINUTES_KEY] = endQuietMinutes;
};

std::string InteriorConfigManager::getPortalName() {
    return INTERIOR_CONFIG_PORTAL_NAME;
}

std::string InteriorConfigManager::getHostname() {
    return this->hostname;
}

void InteriorConfigManager::setHostname(std::string hostname) {
    this->hostname = hostname;
}

uint InteriorConfigManager::getListeningPort() {
    return this->listeningPort;
}

void InteriorConfigManager::setListeningPort(uint listeningPort) {
    this->listeningPort = listeningPort;
}

void InteriorConfigManager::setListeningPort(std::string listeningPort) {
    this->listeningPort = std::atoi(listeningPort.c_str());
}

uint InteriorConfigManager::getTimeoutMinutes() {
    return this->timeoutMinutes;
}

void InteriorConfigManager::setTimeoutMinutes(ulong timeoutMinutes) {
    this->timeoutMinutes = timeoutMinutes;
}

void InteriorConfigManager::setTimeoutMinutes(std::string timeoutMinutes) {
    this->timeoutMinutes = std::atoi(timeoutMinutes.c_str());
}

float InteriorConfigManager::getBatteryVccThreshold() {
    return this->batteryVccThreshold;
}

void InteriorConfigManager::setBatteryVccThreshold(float batteryVccThreshold) {
    this->batteryVccThreshold = batteryVccThreshold;
}

void InteriorConfigManager::setBatteryVccThreshold(std::string batteryVccThreshold) {
    this->batteryVccThreshold = std::atof(batteryVccThreshold.c_str());
}

std::string InteriorConfigManager::getTimezone() {
    return this->timezone;
}

void InteriorConfigManager::setTimezone(std::string timezone) {
    this->timezone = timezone;
}

uint InteriorConfigManager::getStartQuietHours() {
    return this->startQuietHours;
}

void InteriorConfigManager::setStartQuietHours(uint startQuietHours) {
    this->startQuietHours = startQuietHours;
}

void InteriorConfigManager::setStartQuietHours(std::string startQuietHours) {
    this->startQuietHours = std::atoi(startQuietHours.c_str());
}

uint InteriorConfigManager::getStartQuietMinutes() {
    return this->startQuietMinutes;
}

void InteriorConfigManager::setStartQuietMinutes(uint startQuietMinutes) {
    this->startQuietMinutes = startQuietMinutes;
}

void InteriorConfigManager::setStartQuietMinutes(std::string startQuietMinutes) {
    this->startQuietMinutes = std::atoi(startQuietMinutes.c_str());
}

uint InteriorConfigManager::getEndQuietHours() {
    return this->endQuietHours;
}

void InteriorConfigManager::setEndQuietHours(uint endQuietHours) {
    this->endQuietHours = endQuietHours;
}

void InteriorConfigManager::setEndQuietHours(std::string endQuietHours) {
    this->endQuietHours = std::atoi(endQuietHours.c_str());
}

uint InteriorConfigManager::getEndQuietMinutes() {
    return this->endQuietMinutes;
}

void InteriorConfigManager::setEndQuietMinutes(uint endQuietMinutes) {
    this->endQuietMinutes = endQuietMinutes;
}

void InteriorConfigManager::setEndQuietMinutes(std::string endQuietMinutes) {
    this->endQuietMinutes = std::atoi(endQuietMinutes.c_str());
}

void InteriorConfigManager::addParameters(WiFiManager &manager) {
    manager.addParameter(hostnameParam);
    manager.addParameter(listeningPortParam);
    manager.addParameter(timeoutParam);
    manager.addParameter(batteryVccThresholdParam);
    manager.addParameter(timezoneParam);
    manager.addParameter(startQuietHoursParam);
    manager.addParameter(startQuietMinutesParam);
    manager.addParameter(endQuietHoursParam);
    manager.addParameter(endQuietMinutesParam);
}

void InteriorConfigManager::retrieveParameters() {
    setHostname(hostnameParam->getValue());
    setListeningPort(listeningPortParam->getValue());
    setTimeoutMinutes(timeoutParam->getValue());
    setBatteryVccThreshold(batteryVccThresholdParam->getValue());
    setTimezone(timezoneParam->getValue());
    setStartQuietHours(startQuietHoursParam->getValue());
    setStartQuietMinutes(startQuietMinutesParam->getValue());
    setEndQuietHours(endQuietHoursParam->getValue());
    setEndQuietMinutes(endQuietMinutesParam->getValue());
}
