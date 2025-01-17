#include <Arduino.h>
#include <ulatrasound.h>

void iniUlatrasound(int trigPin, int echoPin){
    pinMode(trigPin,OUTPUT);
    pinMode(echoPin,INPUT);
}

float Ulatrasound(int trigPin, int echoPin){
    digitalWrite(trigPin,LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin,HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin,LOW);
    long echoTime = pulseIn(echoPin,HIGH);
    float distance = echoTime * 0.034 / 2; // 聲速約為 343 m/s
    
    if (echoTime == 0) return -1; // 無回應時返回 -1
    return distance;
}

