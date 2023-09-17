#include <Arduino.h>

const int frequency = 5000;
const int resolution = 8;
const u_int8_t channelCount = 10;

class LedConfig
{
  private:
    uint8_t channel;
    uint8_t pin;
    uint8_t color = 255;
    String getParam;
  public:
    LedConfig( uint8_t _channel, uint8_t _pin, String _getParam);

    void setup();

    void setColor(const uint8_t);

    static LedConfig* findByGetParam(const String& _getParam, LedConfig* setupList);
    // static LedSetup findByGetParam(String _getParam, LedSetup* setupList);
};
