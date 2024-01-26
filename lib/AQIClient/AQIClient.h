/**
 * AQIClient.h - AQIClient class definitions
 */

#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>
#include "BME680.h"
#include "GPS.h"

#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"
#define TIME_BETWEEN_PUBLISHES 5000

// JSON key names
#define IAQ "iaq"
#define CO2 "co2"
#define VOC "voc"
#define PRESSURE "pressure"
#define TEMPERATURE "temperature"
#define HUMIDITY "humidity"
#define LOCATION "location"
#define LATITUDE "lat"
#define LONGITUDE "lng"

/**
 * Interfaces the BME680 sensor and NEO-6M GPS module with AWS IoT Core
 *
 * The AQIClient allows sensors to warm up, connects to WiFi and PubSubClient,
 * and periodically publishes updated sensor data to AWS
 */
class AQIClient
{
public:
    // Constructor to initialize WiFiClient, PubSubClient, and time since last publish
    AQIClient();

    // Start the AQIClient, initializing sensors and connecting to WiFi and PubSubClient
    void begin();

    // Run the AQIClient, retrieving and publishing sensor data to AWS
    void run();

private:
    BME680 bme680;
    GPS gps;
    WiFiClientSecure net;
    PubSubClient client;
    unsigned long lastTime;

    // Connect the PubSubClient to AWS IoT Core thing
    void connect();

    // Publish sensor data to the AWS IoT publish topic
    void publish();
};