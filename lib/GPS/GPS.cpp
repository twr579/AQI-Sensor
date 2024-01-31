/**
 * GPS.cpp - GPS class methods
 */

#include "GPS.h"

void GPS::begin()
{
    Serial.println("Establishing GPS connection");
    bool hasFix = false;

    // Wait for the GPS to process a valid location
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

        checkStatus();
    }
    Serial.println("GPS connection established");
}

void GPS::run()
{
    while (Serial2.available() > 0)
    {
        if (gps.encode(Serial2.read()))
        {
            if (gps.location.isValid())
            {
                setData({.lat = gps.location.lat(), .lng = gps.location.lng()});
            }
            else
            {
                Serial.println("Invalid location");
                clear();
            }
        }
    }

    checkStatus();
}

void GPS::checkStatus()
{
    if (millis() > 5000 && gps.charsProcessed() < 10)
    {
        Serial.println("No GPS data received: check wiring");
        clear();
    }
}
