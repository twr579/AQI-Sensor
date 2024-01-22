/**
 * GPS.cpp - GPS library routines
 */

#include "GPS.h"

TinyGPSPlus gps;

void setupGPS()
{
    Serial.println("Establishing GPS connection");
    bool hasFix = false;
    while (!hasFix)
    {
        while (Serial2.available() > 0)
        {
            if (gps.encode(Serial2.read()))
            {
                if (gps.location.isValid())
                {
                    hasFix = true;
                }
            }
        }
    }
    Serial.println("GPS connection established");
}

void runGPS(JsonObject &obj)
{
    while (Serial2.available() > 0)
    {
        if (gps.encode(Serial2.read()))
        {
            if (gps.location.isValid())
            {
                obj[LATITUDE] = gps.location.lat();
                obj[LONGITUDE] = gps.location.lng();
            }
        }
    }
}
