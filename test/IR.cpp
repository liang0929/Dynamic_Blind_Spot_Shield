#include <Arduino.h>

#define in1 2
#define in2 3
#define pwm 5
 
void setup() {
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(pwm,OUTPUT);
}

 
void loop() {
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  analogWrite(pwm,255);
}
