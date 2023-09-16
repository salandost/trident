#include <Arduino.h>
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

const char* ssid     = "HighWiFi";
const char* password = "ffdpffdp";

const int frequency = 5000;
const int resolution = 8;
const int channelCount = 10;

class LedSetup
{
  public:
    uint8_t channel;
    uint8_t pin;
    uint8_t color;
    String getParam;

    LedSetup( uint8_t _channel, uint8_t _pin, uint8_t _getParam);

    void setup();

    void setColor(uint8_t);

    static LedSetup findByGetParam(String _getParam, LedSetup* setupList);
    static LedSetup findByGetParam(String _getParam, LedSetup* setupList);
};

const uint8_t pins[10] =         { 13,   12,   14,   27,   26,   26,   33,   32,   15,   4  };
const String getParamNames[10] = {"sr", "sg", "sb", "mr", "mg", "mb", "lr", "lg", "lb", "wb"};

AsyncWebServer server(80);

uint16_t rgbS[3] = {};
uint16_t rgbM[3] = {};
uint16_t rgbL[3] = {};
uint16_t whiteBrightness = 0;


void notFound(AsyncWebServerRequest*);
void setLedValues(String, String);
const uint16_t f(String); 

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
 
  // WiFi
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println(WiFi.localIP());

  // Led setup
  

  // Server
  server.onNotFound(notFound);

  server.on("/color", HTTP_GET, [](AsyncWebServerRequest *request)
  {
    const AsyncWebParameter* param = request->getParam(1);
    Serial.println(param -> name() + " : " + param -> value());
    request->send(200, "text/plain", "Hello World");
  });
 
  server.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
}

// put function definitions here:
void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
}

void setLedValues(String name, String value) {
  for(String pName: getParamNames) {

  }
}

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
  for(int i = 0; i < channelCount; ++i) 
  {
    if(setupList[i].getParam == getParam)
    {
      return setupList[i];
    }
  }
}
