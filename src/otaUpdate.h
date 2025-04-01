#ifndef DD3A0D08_F73D_4879_A16F_D0AC8A144E13
#define DD3A0D08_F73D_4879_A16F_D0AC8A144E13

#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <HTTPUpdate.h>

class OtaUpdater {
private:
    const char* ssid;
    const char* password;
    const char* firmwareUrl;
    const char* versionUrl;
    String currentVersion;
    int bootButtonPin;

public:
    OtaUpdater(
        const char* wifiSsid, 
        const char* wifiPassword, 
        const char* updateFirmwareUrl, 
        const char* updateVersionUrl,
        const char* deviceVersion = "local-dev",
        int bootPin = 0
    );
    void begin();
    bool isBootButtonPressed();
    void connectToWifi();
    bool checkVersion();
    void checkForUpdates();
    void performUpdate();
    void handle();
};
#endif /* DD3A0D08_F73D_4879_A16F_D0AC8A144E13 */
