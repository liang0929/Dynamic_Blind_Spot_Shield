#include <Arduino.h>
#include <ulatrasound.h>

#define FRONT_TRIG 8
#define FRONT_ECHO 9
#define BACK_TRIG 10
#define BACK_ECHO 11

#define in1 2
#define in2 3
#define pwm 5
#define switch 4

#define THRESHOLD 35
bool isObstacleDetected = false;

void heightControl(int action);

void setup(){
    iniUlatrasound(FRONT_TRIG, FRONT_ECHO);
    iniUlatrasound(BACK_TRIG, BACK_ECHO);
    pinMode(switch, INPUT_PULLUP);
    Serial.begin(9600);
}
void loop(){
    float frontDistance = Ulatrasound(FRONT_TRIG, FRONT_ECHO);
    
    Serial.println(isObstacleDetected);
    float backDistance = Ulatrasound(BACK_TRIG, BACK_ECHO);
      if (frontDistance > 0 && frontDistance <= THRESHOLD && !isObstacleDetected) {
        isObstacleDetected = true;
        heightControl(1);
    }
    // 後方障礙物確認移出
    if (isObstacleDetected && backDistance > 0 && backDistance <= THRESHOLD) {
        isObstacleDetected = false;
        heightControl(0);
    }

    delay(100);
}

void heightControl(int action){
    if (action == 1) {
        Serial.println("上升動作執行");
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        analogWrite(pwm, 255);
        while (digitalRead(switch) == HIGH) {
            delay(10); 
        }
        analogWrite(pwm, 2);
    } else if (action == 0) {
        Serial.println("下降動作執行");
        digitalWrite(in1,LOW);
        digitalWrite(in2,HIGH);
        analogWrite(pwm, 255);
        delay(135);
        analogWrite(pwm, 0);
        digitalWrite(in2,LOW);
    }
}