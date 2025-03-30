#include <Arduino.h>
#include "laser.h"

laser::laser(int Pin){
    laserPin = Pin;
}

void laser::begin(){
    pinMode(laserPin, OUTPUT);
}

void laser::openLaser(){
    digitalWrite(laserPin, HIGH);
}

void laser::closeLaser(){
    digitalWrite(laserPin, LOW);
}