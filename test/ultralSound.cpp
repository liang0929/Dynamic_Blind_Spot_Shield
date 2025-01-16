#include <Arduino.h>

const int trigPin = 6;
const int echoPin = 7;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
}

void loop() {
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  float echoTime = pulseIn(echoPin,HIGH);
  float distance = echoTime/29.4/2;
  Serial.println(distance);
}
