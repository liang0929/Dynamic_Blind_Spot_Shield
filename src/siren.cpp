#include <Arduino.h>
#include <ulatrasound.h>

bool turn = false;

int US1SafeDistance = 50;
int US2SafeDistance = 40;
int US3SafeDistance = 30;

int US1Trig = 2;
int US1Echo = 3;
int US2Trig = 4;
int US2Echo = 5;
int US3Trig = 6;
int US3Echo = 7;

int WarnLight = A0;
int contralSirenSound = A1;
int interruptPin = A2;
int laser = A5;
void setup(){
    Serial.begin(9600);

    iniUlatrasound(US1Trig,US1Echo);
    iniUlatrasound(US2Trig,US2Echo);
    iniUlatrasound(US3Trig,US3Echo);

    pinMode(contralSirenSound,OUTPUT);
    pinMode(WarnLight,OUTPUT);
    pinMode(laser,OUTPUT);
    pinMode(interruptPin,INPUT_PULLUP);
    digitalWrite(laser, LOW);
}

void loop(){
    float US1Val = Ulatrasound(US1Trig, US1Echo);
    float US2Val = Ulatrasound(US2Trig, US2Echo);
    float US3Val = Ulatrasound(US3Trig, US3Echo);
    bool inWarnDistance = US1Val < US1SafeDistance || US2Val < US2SafeDistance || US3Val < US3SafeDistance;  //判斷是否有人進入死角
    digitalWrite(contralSirenSound, LOW);  //關閉警報聲
    digitalWrite(WarnLight, LOW);
    
      //讀取有沒有打方向燈
    Serial.println(digitalRead(interruptPin));
    if(!digitalRead(interruptPin))
    {
        if (inWarnDistance)
        {
            digitalWrite(contralSirenSound, HIGH); //發出警報聲
            digitalWrite(WarnLight, HIGH);
        }else
        {
            digitalWrite(contralSirenSound, LOW);  //關閉警報聲
            digitalWrite(WarnLight, LOW);
        } 
    }
    digitalWrite(laser, LOW);
    delay(10);
    
}
