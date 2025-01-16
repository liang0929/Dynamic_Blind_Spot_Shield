#include <Arduino.h>

void setup(){
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(5,INPUT);
    Serial.begin(9600);
}

void loop(){
    if (digitalRead(5) == HIGH)
    {
        digitalWrite(2,HIGH);
        digitalWrite(3,LOW);
        Serial.println("HIGH");
    }else if (digitalRead(5) == LOW)
    {
        digitalWrite(2,LOW);
        digitalWrite(3,HIGH);
    }
}