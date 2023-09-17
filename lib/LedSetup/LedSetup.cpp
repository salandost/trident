#include "LedSetup.h"

const int frequency = 5000;
const int resolution = 8;

LedSetup::LedSetup( uint8_t _channel, uint8_t _pin, uint8_t _getParam)
{
  this->channel = channel;
  this->pin = _pin;
  this->getParam = _getParam;
}

void LedSetup::setup() {
  ledcSetup(this->channel, frequency, resolution);
  ledcAttachPin(this->pin, this->channel);
}

void LedSetup::setColor(uint8_t _color) {
  if( _color >= 0 && _color <= 255 ) {
    this->color = _color;
  }
}

LedSetup LedSetup::findByGetParam(String getParam, LedSetup* setupList)
{
  for(int i = 0; i < LedSetup::channelCount; ++i) 
  {
    if(setupList[i].getParam == getParam)
    {
      return setupList[i];
    }
  }
}
