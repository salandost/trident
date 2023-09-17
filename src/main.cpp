#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <LedSetup.h>

const char* ssid     = "HighWiFi";
const char* password = "ffdpffdp";

const uint8_t pins[10] =         { 13,   12,   14,   27,   26,   26,   33,   32,   15,   4  };
const String getParamNames[10] = {"sr", "sg", "sb", "mr", "mg", "mb", "lr", "lg", "lb", "wb"};

AsyncWebServer server(80);

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

  server.on("/color", HTTP_GET, handleColor);
 
  server.begin();
}

void loop()
{
  // put your main code here, to run repeatedly:
}

// put function definitions here:
void handleNotFound(AsyncWebServerRequest *request)
{
  request->send(404, "application/json", "{\"message\":\"Not found\"}");
}

void handleColor(AsyncWebServerRequest *request)
{
  const AsyncWebParameter* param = request->getParam(1);
  Serial.println(param -> name() + " : " + param -> value());
  request->send(200, "text/plain", "Hello World");
}
