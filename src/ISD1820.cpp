#include <Arduino.h>
#include "ISD1820.h"

ISD1820::ISD1820(int playEPin){
    playEPin = playEPin;
}

void ISD1820::begin(){
    pinMode(playEPin, OUTPUT);
}

void ISD1820::playSound(){
    digitalWrite(playEPin, HIGH);
}

void ISD1820::closeSound(){
    digitalWrite(playEPin, LOW);
}
