/**
 * Bme680.cpp - BME680 library routines
 */

#include "Bme680.h"

// Create an object of the class Bsec
Bsec bme680;

void setupBme680()
{
    bme680.begin(BME68X_I2C_ADDR_HIGH, Wire);
    checkSensorStatus();

    bsec_virtual_sensor_t sensorList[6] = {
        BSEC_OUTPUT_IAQ,
        BSEC_OUTPUT_CO2_EQUIVALENT,
        BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
        BSEC_OUTPUT_RAW_PRESSURE,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    };

    bme680.updateSubscription(sensorList, 6, BSEC_SAMPLE_RATE_LP);
    checkSensorStatus();

    Serial.println("Sensor warming up");
    while (!bme680.iaqAccuracy)
    {
        bme680.run();
    };
    Serial.println("Sensor warmed up");
}

void runBme680(JsonDocument &doc)
{
    if (bme680.run())
    { // If new data is available
        doc[IAQ] = String(bme680.iaq);
        doc[CO2] = String(bme680.co2Equivalent);
        doc[VOC] = String(bme680.breathVocEquivalent);
        doc[PRESSURE] = String(bme680.pressure);
        doc[TEMPERATURE] = String(bme680.temperature);
        doc[HUMIDITY] = String(bme680.humidity);
    }
    else
    {
        checkSensorStatus();
    }
}

void checkSensorStatus()
{
    String errorStr = "BSEC error code: ";
    String warningStr = "BSEC warning code: ";
    if (bme680.bsecStatus != BSEC_OK)
    {
        if (bme680.bsecStatus < BSEC_OK)
        {
            Serial.println(errorStr + bme680.bsecStatus);
        }
        else
        {
            Serial.println(warningStr + bme680.bsecStatus);
        }
    }

    if (bme680.bme68xStatus != BME68X_OK)
    {
        if (bme680.bme68xStatus < BME68X_OK)
        {
            Serial.println(errorStr + bme680.bme68xStatus);
        }
        else
        {
            Serial.println(warningStr + bme680.bme68xStatus);
        }
    }
}
