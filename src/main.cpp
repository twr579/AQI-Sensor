#include "Bme680.h"
#include "AWS.h"
#include <ArduinoJson.h>

void setup()
{
  /* Initializes the Serial communication */
  Serial.begin(115200);
  delay(1000);
  pinMode(LED_BUILTIN, OUTPUT);
  setupAWS();
  setupBme680();
}

void loop()
{
  JsonDocument doc;

  runBme680(doc);

  if (!doc.isNull())
  {
    publish(doc);
  }
}