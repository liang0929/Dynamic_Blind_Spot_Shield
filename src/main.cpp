#include <Arduino.h>
#include "otaUpdate.h"
#include "HCSR04.h"
#include "ISD1820.h"
#include "laser.h"
#include "motor.h"

HCSR04 HCSR04_0(0,1);
HCSR04 HCSR04_1(0,1);
HCSR04 HCSR04_2(0,1);
HCSR04 HCSR04_3(0,1);
HCSR04 HCSR04_4(0,1);

ISD1820 voiceRecoder(0);

laser waringLine(0);

motor Motor(15);

void setup(){

    HCSR04_0.begin();
    HCSR04_1.begin();
    HCSR04_2.begin();
    HCSR04_3.begin();
    HCSR04_4.begin();

    voiceRecoder.begin();

    waringLine.begin();

    Motor.begin();
}
void loop(){
    
}