/**
 * BME680.cpp - BME680 class methods
 */

#include "BME680.h"

void BME680::begin()
{
    bsec.begin(BME68X_I2C_ADDR_HIGH, Wire);
    checkStatus();

    bsec_virtual_sensor_t sensorList[6] = {
        BSEC_OUTPUT_IAQ,
        BSEC_OUTPUT_CO2_EQUIVALENT,
        BSEC_OUTPUT_BREATH_VOC_EQUIVALENT,
        BSEC_OUTPUT_RAW_PRESSURE,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_TEMPERATURE,
        BSEC_OUTPUT_SENSOR_HEAT_COMPENSATED_HUMIDITY,
    };

    bsec.updateSubscription(sensorList, 6, BSEC_SAMPLE_RATE_LP);
    checkStatus();

    Serial.println("Sensor warming up");

    // Run the sensor until it is calibrated
    while (!bsec.iaqAccuracy)
    {
        bsec.run();
    };

    Serial.println("Sensor warmed up");
}

void BME680::run()
{
    if (bsec.run())
    { // If new data is available
        setData({
            .iaq = bsec.iaq,
            .co2 = bsec.co2Equivalent,
            .voc = bsec.breathVocEquivalent,
            .pressure = bsec.pressure,
            .temperature = bsec.temperature,
            .humidity = bsec.humidity,
        });
    }
    else
    {
        checkStatus();
    }
}

void BME680::checkStatus()
{
    String errorStr = "BSEC error code: ";
    String warningStr = "BSEC warning code: ";
    if (bsec.bsecStatus != BSEC_OK)
    {
        clear();
        if (bsec.bsecStatus < BSEC_OK)
        {
            Serial.println(errorStr + bsec.bsecStatus);
        }
        else
        {
            Serial.println(warningStr + bsec.bsecStatus);
        }
    }

    if (bsec.bme68xStatus != BME68X_OK)
    {
        clear();
        if (bsec.bme68xStatus < BME68X_OK)
        {
            Serial.println(errorStr + bsec.bme68xStatus);
        }
        else
        {
            Serial.println(warningStr + bsec.bme68xStatus);
        }
    }
}
