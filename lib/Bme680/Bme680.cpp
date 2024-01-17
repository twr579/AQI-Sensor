/**
 * Bme680.cpp - BME680 library routines
 */

#include "Bme680.h"

// JSON key names definitions
#define IAQ "IAQ"
#define CO2 "CO2"
#define VOC "VOC"
#define PRESSURE "pressure"
#define TEMPERATURE "temperature"
#define HUMIDITY "humidity"

// Create an object of the class Bsec
Bsec bme680;

String output;

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

    // Print the header
    output = "Timestamp [ms], IAQ, IAQ accuracy, CO2 equivalent, breath VOC equivalent, pressure [hPa], comp temp[°C], comp humidity [%]";
    Serial.println(output);
}

void runBme680(JsonDocument &doc)
{
    if (bme680.run())
    { // If new data is available
        digitalWrite(LED_BUILTIN, LOW);
        output = String(bme680.iaq);
        output += ", " + String(bme680.iaqAccuracy);
        output += ", " + String(bme680.co2Equivalent);
        output += ", " + String(bme680.breathVocEquivalent);
        output += ", " + String(bme680.pressure);
        output += ", " + String(bme680.temperature);
        output += ", " + String(bme680.humidity);
        Serial.println(output);
        digitalWrite(LED_BUILTIN, HIGH);

        if (bme680.iaqAccuracy)
        { // If sensor data is accurate, populate a JsonDocument to publish to DynamoDB
            doc[IAQ] = String(bme680.iaq);
            doc[CO2] = String(bme680.co2Equivalent);
            doc[VOC] = String(bme680.breathVocEquivalent);
            doc[PRESSURE] = String(bme680.pressure);
            doc[TEMPERATURE] = String(bme680.temperature);
            doc[HUMIDITY] = String(bme680.humidity);
        }
    }
    else
    {
        checkSensorStatus();
    }
}

void checkSensorStatus()
{
    if (bme680.bsecStatus != BSEC_OK)
    {
        if (bme680.bsecStatus < BSEC_OK)
        {
            output = "BSEC error code : " + String(bme680.bsecStatus);
            Serial.println(output);
        }
        else
        {
            output = "BSEC warning code : " + String(bme680.bsecStatus);
            Serial.println(output);
        }
    }

    if (bme680.bme68xStatus != BME68X_OK)
    {
        if (bme680.bme68xStatus < BME68X_OK)
        {
            output = "BME68X error code : " + String(bme680.bme68xStatus);
            Serial.println(output);
        }
        else
        {
            output = "BME68X warning code : " + String(bme680.bme68xStatus);
            Serial.println(output);
        }
    }
}
