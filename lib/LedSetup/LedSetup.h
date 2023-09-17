#include <Arduino.h>

class LedSetup
{
  public:
    uint8_t channel;
    uint8_t pin;
    uint8_t color;
    String getParam;
    static const u_int8_t channelCount = 10;

    LedSetup( uint8_t _channel, uint8_t _pin, uint8_t _getParam);

    void setup();

    void setColor(uint8_t);

    static LedSetup findByGetParam(String _getParam, LedSetup* setupList);
    // static LedSetup findByGetParam(String _getParam, LedSetup* setupList);
};
