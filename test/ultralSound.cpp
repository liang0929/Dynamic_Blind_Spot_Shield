#include <Arduino.h>
#include <ulatrasound.h>
#include "GuardrailConstants.h"

void setup() {
  Serial.begin(9600);
  iniUlatrasound(BACK_TRIG, BACK_ECHO);
}

void loop() {
  float frontDistance = Ulatrasound(BACK_TRIG, BACK_ECHO);
  Serial.println(frontDistance);
}
