/**
 * GPS.h - GPS library routines
 */

#include <TinyGPS++.h>
#include <ArduinoJson.h>

// JSON key names definitions
#define LATITUDE "lat"
#define LONGITUDE "lng"

// Initializes the GPS for use
void setupGPS();

/**
 * Reads data from the GPS and populates a JsonObject with relevant GPS data to publish to DynamoDB.
 *
 * @param[out] obj a reference to a JsonObject containing GPS data
 */
void runGPS(JsonObject &obj);