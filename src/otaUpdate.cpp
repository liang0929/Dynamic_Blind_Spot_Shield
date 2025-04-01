#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>
#include "otaUpdate.h"

OtaUpdater::OtaUpdater(
    const char* wifiSsid, 
    const char* wifiPassword, 
    const char* updateFirmwareUrl, 
    const char* updateVersionUrl,
    const char* deviceVersion,
    int bootPin
    ) {
    ssid = wifiSsid;
    password = wifiPassword;
    firmwareUrl = updateFirmwareUrl;
    versionUrl = updateVersionUrl;
    currentVersion = deviceVersion;
    bootButtonPin = bootPin;
}

void OtaUpdater::begin() {
    pinMode(bootButtonPin, INPUT_PULLUP);
}

bool OtaUpdater::isBootButtonPressed() {
    return (digitalRead(bootButtonPin) == LOW);
}

void OtaUpdater::connectToWifi() {
    Serial.print("連接wifi中");
    WiFi.begin(ssid, password);

    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED && timeout < 20) {
        delay(500);
        Serial.print(".");
        timeout++;
    }
    
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("已連接!");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("連接失敗!");
    }
}

bool OtaUpdater::checkVersion() {
    HTTPClient http;
    http.begin(versionUrl);
    int httpCode = http.GET();
    
    if (httpCode == 200) {
        String newVersion = http.getString();
        newVersion.trim();
        
        Serial.print("現在版本: ");
        Serial.println(currentVersion);
        Serial.print("可更新版本: ");
        Serial.println(newVersion);
        
        http.end();
        
        if (newVersion != currentVersion) {
            Serial.println("有新版本!");
            return true;
        } else {
            Serial.println("已是最新版");
            return false;
        }
    } else {
        Serial.print("檢查版本失敗, HTTP code: ");
        Serial.println(httpCode);
        http.end();
        return false;
    }
}

void OtaUpdater::checkForUpdates() {
    if (WiFi.status() != WL_CONNECTED) {
        connectToWifi();
        if (WiFi.status() != WL_CONNECTED) {
            Serial.println("WiFi未連接，版本檢查失敗");
            return;
        }
    }
    
    Serial.println("檢查韌體更新");
    
    if (checkVersion()) {
        Serial.println("可更新，正在更新");
        performUpdate();
    } else {
        Serial.println("不需更新");
    }
}

void OtaUpdater::performUpdate() {
        Serial.println("開始OTA更新");
        
        WiFiClient client;
        
        httpUpdate.setLedPin(LED_BUILTIN, LOW);
        
        t_httpUpdate_return ret = httpUpdate.update(client, firmwareUrl);

        switch (ret) {
            case HTTP_UPDATE_FAILED:
                Serial.printf("HTTP_UPDATE_FAILED Error (%d): %s\n", 
                    httpUpdate.getLastError(), httpUpdate.getLastErrorString().c_str());
                break;
                
            case HTTP_UPDATE_NO_UPDATES:
                Serial.println("HTTP_UPDATE_NO_UPDATES");
                break;
                
            case HTTP_UPDATE_OK:
                Serial.println("HTTP_UPDATE_OK");
                break;
        }
    }

void OtaUpdater::handle() {
    if (isBootButtonPressed()) {
        Serial.println("Boot被按下正在檢查更新");
        delay(500);
        while (isBootButtonPressed()) {
            delay(10);
        }
        
        checkForUpdates();
    }
}