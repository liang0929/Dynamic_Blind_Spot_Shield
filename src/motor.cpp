#include <Arduino.h>
#include "motor.h"

motor::motor(int PIN, int IN_A, int IN_B){
    GPIOPIN = PIN;
    IN_A = IN_A;
    IN_B = IN_B;
}

void motor::begin(){
    ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOUTION);
    ledcAttachPin(GPIOPIN, PWM_CHANNEL);
}

void motor::motorControl(int power, int direction){
    uint32_t dutyCycle = map(power, 0, 255, 0, 100);
    switch (direction)
    {
    case 1:
        digitalWrite(IN_A, HIGH);
        digitalWrite(IN_B, LOW);
        break;

    case -1:
        digitalWrite(IN_A, LOW);
        digitalWrite(IN_B, HIGH);
        break;

    default:
        digitalWrite(IN_A, LOW);
        digitalWrite(IN_B, LOW);
        break;
    }

    ledcWrite(PWM_CHANNEL, dutyCycle);
}



