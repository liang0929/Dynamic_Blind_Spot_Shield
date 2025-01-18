#include <Arduino.h>
#include <air_pump.h>
#include <ulatrasound.h>

int frontTrigPin = 2;
int backTrigPin = 4;
int frontEchoPin = 7;
int backEchopin = 8;

int airPumpPin = 5;

void setup(){
    iniAirPump(airPumpPin);
    iniUlatrasound(frontTrigPin, frontEchoPin);
    iniUlatrasound(backTrigPin, backEchopin);
}

void loop(){
    float frontVal = Ulatrasound(frontTrigPin, frontEchoPin);

    if (frontVal < 20) airPump(airPumpPin, true);
    else
    {
        delay(2000);
        airPump(airPumpPin, false);
    }
}