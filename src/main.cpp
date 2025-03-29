#include <Arduino.h>
#include "HCSR04.h"

HCSR04 HCSR04_0(0,1);
HCSR04 HCSR04_1(0,1);
HCSR04 HCSR04_2(0,1);
HCSR04 HCSR04_3(0,1);
HCSR04 HCSR04_4(0,1);

void setup(){

    HCSR04_0.begin();
    HCSR04_1.begin();
    HCSR04_2.begin();
    HCSR04_3.begin();
    HCSR04_4.begin();
}
void loop(){
    
}