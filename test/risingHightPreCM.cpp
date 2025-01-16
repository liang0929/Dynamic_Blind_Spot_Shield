#include <Arduino.h>
#include <Servo.h>

Servo myservo;

const float risingHightPreCM = 1.0;

void setup(){
    myservo.attach(9);
}

void loop(){
    myservo.write(22);    //旋轉到22度，就是下歸零
    delay(1000);
    myservo.write(22 + 1 * risingHightPreCM);  
    delay(1000000);
}