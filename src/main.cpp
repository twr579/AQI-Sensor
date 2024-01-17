#include "Bme680.h"
#include <ArduinoJson.h>

void setup()
{
  /* Initializes the Serial communication */
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  setupBme680();
}

void loop()
{
  JsonDocument doc;
  runBme680(doc);
  if (!doc.isNull())
  {
    serializeJson(doc, Serial);
  }
}