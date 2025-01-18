#include <Arduino.h>
#include <ulatrasound.h>

#define FRONT_TRIG 8
#define FRONT_ECHO 9
#define BACK_TRIG 10
#define BACK_ECHO 11

#define in1 2
#define in2 3
#define pwm 5
#define switchPin 4

#define THRESHOLD 35
bool isObstacleDetected = false;

void heightControl(int action);

void setup() {
    iniUlatrasound(FRONT_TRIG, FRONT_ECHO);
    iniUlatrasound(BACK_TRIG, BACK_ECHO);
    pinMode(switchPin, INPUT_PULLUP);
    Serial.begin(9600);
}

void loop() {
    float frontDistance = Ulatrasound(FRONT_TRIG, FRONT_ECHO);
    float backDistance = Ulatrasound(BACK_TRIG, BACK_ECHO);
    
    Serial.println(isObstacleDetected);

    // 前方障礙物檢測並執行上升
    if (frontDistance > 0 && frontDistance <= THRESHOLD && !isObstacleDetected) {
        isObstacleDetected = true;
        heightControl(1);  // 執行上升
    }

    // 後方障礙物確認移出並執行下降
    if (isObstacleDetected && backDistance > 0 && backDistance <= THRESHOLD) {
        isObstacleDetected = false;
        heightControl(0);  // 執行下降
    }

    delay(100);
}

void heightControl(int action) {
    if (action == 1) {
        Serial.println("上升動作執行");
        digitalWrite(in1, HIGH);
        digitalWrite(in2, LOW);
        analogWrite(pwm, 255);

        // 檢查微動開關，直到觸發為止
        while (digitalRead(switchPin) == HIGH) {
            delay(10); 
        }

        analogWrite(pwm, 0); // 停止馬達
        Serial.println("上升動作完成");
    } 
    else if (action == 0) {
        Serial.println("下降動作執行");
        digitalWrite(in1, LOW);
        digitalWrite(in2, HIGH);
        analogWrite(pwm, 255);

        // 在下降過程中檢測前方障礙物
        while (true) {
            float frontDistance = Ulatrasound(FRONT_TRIG, FRONT_ECHO);

            // 若檢測到障礙物，立即中斷下降並執行上升
            if (frontDistance > 0 && frontDistance <= THRESHOLD) {
                Serial.println("下降中檢測到障礙物，立即上升");
                analogWrite(pwm, 0);  // 停止下降
                heightControl(1);     // 切換到上升
                return;               // 結束當前的下降函式
            }

            delay(10); // 減少頻繁檢測
        }

        analogWrite(pwm, 0); // 停止馬達
        digitalWrite(in2, LOW);
        Serial.println("下降動作完成");
    }
}
