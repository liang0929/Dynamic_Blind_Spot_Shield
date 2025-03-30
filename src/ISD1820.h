#ifndef D94D9115_58F7_4479_81D7_D0D956A128A8
#define D94D9115_58F7_4479_81D7_D0D956A128A8

class ISD1820
{
private:
    int playEPin;
public:
    ISD1820(int playEPin);
    void begin();
    void playSound();
    void closeSound();
};

#endif /* D94D9115_58F7_4479_81D7_D0D956A128A8 */
