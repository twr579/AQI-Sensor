#include <Arduino.h>
#include "AQIClient.h"

AQIClient aqiClient;

void setup()
{
  /* Initializes the Serial communication */
  Serial.begin(115200);
  Serial2.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  aqiClient.begin();
}

void loop()
{
  aqiClient.run();
}