#include <Arduino.h>
#include "motor.h"

motor::motor(int GPIOPIN){
    GPIOPIN = GPIOPIN;
}

void motor::begin(){
    ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOUTION);
    ledcAttachPin(GPIOPIN, PWM_CHANNEL);
}

void motor::motorControl(int dutyCycle){
    ledcWrite(PWM_CHANNEL, dutyCycle);
}



