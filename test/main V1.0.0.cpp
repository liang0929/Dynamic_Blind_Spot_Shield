#include <Arduino.h>
#include <ulatrasound.h>
#include <Servo.h>

Servo mg300servo;
int servoPin = 9;

int frontTrigPin = 2;
int backTrigPin = 4;
int frontEchoPin = 7;
int backEchopin = 8;

const float height = 15;
float heightStandard;
const float risingHightPreCM = 5.0;
int servoAngle;

void setup(){
    mg300servo.attach(servoPin);
    Serial.begin(9600);
    iniUlatrasound(frontTrigPin, frontEchoPin);
    iniUlatrasound(backTrigPin, backEchopin);
    
}

void loop(){
    //讀取前後超音波的高度
    float frontUlatrasoundVal = Ulatrasound(frontTrigPin,frontEchoPin);
    float backUlatrasoundVal = Ulatrasound(backTrigPin,backEchopin);
    //比較前後超音波高度，並取高度小的為參考高度
    if(frontUlatrasoundVal > backUlatrasoundVal){
        heightStandard = backUlatrasoundVal; 
    }else if (frontUlatrasoundVal < backUlatrasoundVal){
        heightStandard = frontUlatrasoundVal;
    }else{
        heightStandard = frontUlatrasoundVal;
    }
    
    if (heightStandard > height)
    {
        heightStandard = height;
    }
    
    //高度轉換成伺服馬達要轉的角度
    servoAngle = static_cast<int>((height-heightStandard)*risingHightPreCM+22);
    
    mg300servo.write(servoAngle);  //旋轉角度
    delay(100);
}