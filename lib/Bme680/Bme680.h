/**
 * Bme680.h - BME680 library routines
 */

#include "bsec.h"
#include <ArduinoJson.h>

// Initializes the BME680 sensor for use
void setupBme680();

/**
 * Reads data from the sensor, and if the data is new and accurate (i.e. sensor has warmed up),
 * populates a JsonDocument with relevant sensor data to publish to DynamoDB.
 *
 * @param[out] doc a reference to a JsonDocument containing sensor data
 */
void runBme680(JsonDocument &doc);

// Checks for error or warning codes if the sensor is not running properly
void checkSensorStatus();