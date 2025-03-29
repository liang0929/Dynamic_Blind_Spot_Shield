#include "HCSR04.h"

HCSR04::HCSR04(int trig, int echo){
    trigPin = trig;
    echoPin = echo;
}

void HCSR04::begin(){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float HCSR04::measureDistance(){
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

   long duration = pulseIn(echoPin, HIGH);
   float distanceCm = duration * 0.034 / 2;
    
   return distanceCm;
}