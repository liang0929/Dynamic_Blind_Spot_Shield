#ifndef F32001C5_CF8A_4EF3_AB84_4695EB597DAD
#define F32001C5_CF8A_4EF3_AB84_4695EB597DAD

class laser
{
private:
    int laserPin;
public:
    laser(int laserPin);
    void begin();
    void openLaser();
    void closeLaser();
};

#endif /* F32001C5_CF8A_4EF3_AB84_4695EB597DAD */
