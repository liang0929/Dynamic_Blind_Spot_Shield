#include <Arduino.h>
#include "config.h"
#include "otaUpdate.h"
#include "HCSR04.h"
#include "ISD1820.h"
#include "laser.h"
#include "motor.h"

const char* wifiSsid = WifiSsid;
const char* wifiPassword = WifiPassword;
const char* updateFirmwareUrl = UpdateFirmwareUrl;
const char* updateVersionUrl = UpdateVersionUrl;

bool state = false;

HCSR04 HCSR04_0(US0Trig,US0echo);
HCSR04 HCSR04_1(US1Trig,US1echo);
HCSR04 HCSR04_2(US2Trig,US2echo);
HCSR04 HCSR04_3(US3Trig,US3echo);
HCSR04 HCSR04_4(US4Trig,US4echo);

ISD1820 voiceRecoder(voicePin);

laser waringLine(laserPin);

motor Motor(DCmotor, IN_A, IN_B);

OtaUpdater otaUpdater(wifiSsid, wifiPassword, updateFirmwareUrl, updateVersionUrl);

void heightControl(int action);

void setup(){

    HCSR04_0.begin();
    HCSR04_1.begin();
    HCSR04_2.begin();
    HCSR04_3.begin();
    HCSR04_4.begin();

    voiceRecoder.begin();

    waringLine.begin();

    Motor.begin();

    pinMode(enforcementMode, PULLDOWN);
    pinMode(USerroligh, PULLDOWN);
}
void loop(){
    if (HCSR04_0.measureDistance() == -1 || HCSR04_0.measureDistance() == -1){
        digitalWrite(USerroligh, HIGH);
    }
    if (digitalRead(enforcementMode)){
        heightControl(1);
    }else{
        if (HCSR04_0.measureDistance() < THRESHOLD ){
            heightControl(1);
        }
    }
}

void heightControl(int action){
    switch (action)
    {
    case 1: //上升
        Motor.motorControl(100, 1);
        while (digitalRead(microSwitch))
        Motor.motorControl(100, 0);
        state = true;
        break;
    
    case 2: //下降
        unsigned long startTime = millis();
        Motor.motorControl(100,-1);
        while (millis() - startTime < 10) {
            float frontDistance = HCSR04_0.measureDistance();
            if (frontDistance > 0 && frontDistance <= THRESHOLD) {
                Motor.motorControl(100, 0);
                heightControl(1);     // 切換到上升
                return;               // 結束當前的下降函式
            }
        }
        Motor.motorControl(100, 0);
        state = false;
        break;
    default:
        break;
    }
}