#include <Arduino.h>
#include "GuardrailConstants.h"
void setup(){
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);
    pinMode(pwm,OUTPUT);
    pinMode(switchPin, INPUT_PULLUP);
}
void loop(){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    analogWrite(pwm, 200);

    // 檢查微動開關，直到觸發為止
    while (digitalRead(switchPin) == HIGH) {
        delay(1);
    }
    analogWrite(pwm, 30); // 停止馬達
}
