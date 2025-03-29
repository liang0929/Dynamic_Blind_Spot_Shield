#ifndef B5A72F0E_E237_423B_96A5_4FD1C4419053
#define B5A72F0E_E237_423B_96A5_4FD1C4419053

#include <Arduino.h>

class HCSR04{
private:
    int trigPin;
    int echoPin;
public:
    HCSR04(int trigPin, int echoPin);
    void begin();
    float measureDistance();
}; 

#endif /* B5A72F0E_E237_423B_96A5_4FD1C4419053 */
