#include <Arduino.h>
#include <ulatrasound.h>
#include "GuardrailConstants.h"


void heightControl(int action);
bool isObstacleDetected = false;
int frontSensorHeight = 48;
int backSensorHeight = 37;

void setup() {
    iniUlatrasound(FRONT_TRIG, FRONT_ECHO);
    iniUlatrasound(BACK_TRIG, BACK_ECHO);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(pwm,OUTPUT);
    pinMode(switchPin, INPUT_PULLUP);
    pinMode(setSensorHeight, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
    float frontDistance = Ulatrasound(FRONT_TRIG, FRONT_ECHO);
    float backDistance = Ulatrasound(BACK_TRIG, BACK_ECHO);
    Serial.println(frontDistance);
    Serial.println(backDistance);
    if (frontDistance == -1 || backDistance == -1)
    {
        digitalWrite(errolight, HIGH);
    }else
    {
        digitalWrite(errolight, LOW);
        if (digitalRead(setSensorHeight) == LOW)
        {
            frontDistance = frontSensorHeight;
            backDistance = backSensorHeight;
        }
        if (digitalRead(enforcementMode) == LOW) // 強制執行上升
        {   isObstacleDetected = true;
            heightControl(1);  // 執行上升
        }else
        {
  
            // 前方障礙物檢測並執行上升
            if (frontDistance > 0 && frontSensorHeight - frontDistance >= THRESHOLD && !isObstacleDetected) {
                isObstacleDetected = true;
                heightControl(1);  // 執行上升
            }

            // 後方障礙物確認移出並執行下降
            if (isObstacleDetected && backDistance > 0 && backSensorHeight - backDistance >= THRESHOLD) {
                isObstacleDetected = false;
                heightControl(0);  // 執行下降
            }
        }
        
    }
    delay(100);
}

void heightControl(int action) {
    if (action == 1) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(pwm, 100);
        Serial.println("up");
        // 檢查微動開關，直到觸發為止
        while (digitalRead(switchPin) == HIGH) {
            delay(1);
        }
        Serial.println("微動開關觸發");
        analogWrite(pwm, 30); // 停止馬達
    } 
    else if (action == 0) {
        digitalWrite(in1, LOW);

        digitalWrite(in2, HIGH);
        analogWrite(pwm, 50);
        unsigned long startTime = millis();
        // 在下降過程中檢測前方障礙物
        Serial.println("DOWN");
        while (millis() - startTime < 10) {
            float frontDistance = Ulatrasound(FRONT_TRIG, FRONT_ECHO);
            // 若檢測到障礙物，立即中斷下降並執行上升
            if (frontDistance > 0 && frontDistance <= THRESHOLD) {
                analogWrite(pwm, 0);  // 停止下降
                heightControl(1);     // 切換到上升
                return;               // 結束當前的下降函式
            }
        }
        analogWrite(pwm, 30); // 停止馬達
    }
}
