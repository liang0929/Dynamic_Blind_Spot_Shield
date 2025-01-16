#include <Arduino.h>
#include <air_pump.h>
void iniAirPump(unsigned pin){
    pinMode(pin, OUTPUT);
}

void airPump(unsigned pin, bool state){

    if (state){
        digitalWrite(pin,HIGH);
    }else{
        digitalWrite(pin,LOW);
    }
    
}