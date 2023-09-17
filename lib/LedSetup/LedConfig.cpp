#include "LedConfig.h"

LedConfig::LedConfig( uint8_t _channel, uint8_t _pin, String _getParam)
{
  this->channel = _channel;
  this->pin = _pin;
  this->getParam = _getParam;
}

void LedConfig::setup() {
  ledcSetup(this->channel, frequency, resolution);
  ledcAttachPin(this->pin, this->channel);
  Serial.println(this->pin);
  Serial.println(this->channel);
}

void LedConfig::setColor(const uint8_t _color) {
  if( _color != this->color && _color >= 0 && _color <= 255 ) {
    this->color = _color;
    ledcWrite(this->channel, this->color);
  }
}

LedConfig* LedConfig::findByGetParam(const String& getParam, LedConfig* setupList)
{
  for(int i = 0; i < channelCount; ++i) 
  {
    if(setupList[i].getParam == getParam)
    {
      return &setupList[i];
    }
  }
  return nullptr;
}
