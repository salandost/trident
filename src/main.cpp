#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LedConfig.h>

const char* ssid     = "HighWiFi";
const char* password = "ffdpffdp";

LedConfig leds[channelCount] =
{
  LedConfig(0, 13, "sr"),
  LedConfig(1, 12, "sg"),
  LedConfig(2, 14, "sb"),
  LedConfig(3, 27, "mr"),
  LedConfig(4, 26, "mg"),
  LedConfig(5, 25, "mb"),
  LedConfig(6, 33, "lr"),
  LedConfig(7, 32, "lg"),
  LedConfig(8, 15, "lb"),
  LedConfig(9, 4,  "wb"),
};

AsyncWebServer server(80);

void handleNotFound(AsyncWebServerRequest*);
void setLedValues(String, String);
void handleColor(AsyncWebServerRequest*);
const uint16_t f(String); 

void setup()
{
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
  for(auto led : leds) {
    led.setup();
  }

  // Server
  server.onNotFound(handleNotFound);
  server.on("/color", HTTP_GET, handleColor);
  server.begin();
}

void loop() {}

// put function definitions here:
void handleNotFound(AsyncWebServerRequest *request)
{
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
}

void handleColor(AsyncWebServerRequest *request)
{
  for(int paramIndex = 0; paramIndex < request -> params(); ++paramIndex) {
      const AsyncWebParameter* param = request -> getParam(paramIndex);
      LedConfig* currentConfig = LedConfig::findByGetParam(param -> name(), leds);
      Serial.println(param->name() + " : " + param-> value());
      if (currentConfig != nullptr )
        currentConfig -> setColor(param -> value().toInt());
      else
        request->send(400, "application/json", "{\"message\":\"error\"}");
  }
  request->send(200, "application/json", "{\"message\":\"ok\"}");
}
