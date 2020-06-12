#include "ConfigManager.h"

#include <FS.h>

#define CONFIG_JSON_PATH "/config.json"

void ConfigManager::load() {
    Serial.print("Mounting FS... ");
    if (!SPIFFS.begin()) {
        Serial.println("failed");
    } else {
        Serial.println("success");
        if (!SPIFFS.exists(CONFIG_JSON_PATH)) {
            Serial.println("No previous config found. Skipping.");
        } else {
            Serial.print("Opening config file... ");
            File configFile = SPIFFS.open(CONFIG_JSON_PATH, "r");
            if (!configFile) {
                Serial.println("failed.");
            } else {
                Serial.println("success.");
                Serial.print("Reading config file... ");
                size_t size = configFile.size();
                std::unique_ptr<char[]> buf(new char[size]);
                configFile.readBytes(buf.get(), size);
                DynamicJsonDocument doc(1024);
                if (!deserializeJson(doc, buf.get())) {
                    Serial.println("success.");
                    readJson(doc);
                } else {
                    Serial.println("failed.");
                }
                configFile.close();
            }
        }
    }
}

void ConfigManager::save() {
    Serial.println("Retrieving parameters...");
    retrieveParameters();

    Serial.println("Saving config...");

    DynamicJsonDocument doc(1024);
    writeJson(doc);

    Serial.print("Saving config file... ");
    File configFile = SPIFFS.open(CONFIG_JSON_PATH, "w");
    if (!configFile) {
        Serial.println("failed.");
    } else {
        Serial.println("success.");
        serializeJson(doc, Serial);
        serializeJson(doc, configFile);
        configFile.close();
    }
}

void ConfigManager::formatFS() {
    SPIFFS.format();
}

void ConfigManager::configure() {
    WiFiManager wifiManager;
    wifiManager.setSaveConfigCallback(std::bind(&ConfigManager::save, this));
    wifiManager.setConfigPortalTimeout(60);
    addParameters(wifiManager);
    wifiManager.startConfigPortal(getPortalName().c_str());
    ESP.restart();
}
