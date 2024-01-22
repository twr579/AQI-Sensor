#include "Bme680.h"
#include "AWS.h"
#include "GPS.h"
#include <ArduinoJson.h>

#define TIME_BETWEEN_READS 5000
#define LOCATION "location"

unsigned long lastTime = 0;

void setup()
{
  /* Initializes the Serial communication */
  Serial.begin(115200);
  Serial2.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  setupBme680();
  setupGPS();
  setupAWS();
}

void loop()
{
  if ((millis() - lastTime) > TIME_BETWEEN_READS)
  {
    JsonDocument doc;
    JsonObject location = doc[LOCATION].to<JsonObject>();
    runBme680(doc);
    runGPS(location);
    publish(doc);
    lastTime = millis();
  }
}