#ifndef E8B91FC9_7EF1_4FEE_8C38_96BA6E9EB7F3
#define E8B91FC9_7EF1_4FEE_8C38_96BA6E9EB7F3

class motor
{
private:
    int PWM_FREQUENCY = 5000; 
    int PWM_CHANNEL = 0;
    int PWM_RESOUTION = 8; 
    int GPIOPIN; 
    int IN_A;
    int IN_B;
public:
    motor(int GPIOPIN, int IN_A, int IN_B);
    void begin();
    void motorControl(int power, int direction);
};

#endif /* E8B91FC9_7EF1_4FEE_8C38_96BA6E9EB7F3 */
