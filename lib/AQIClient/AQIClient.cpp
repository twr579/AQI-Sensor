/**
 * AQIClient.cpp - AQIClient class methods
 */

#include "AQIClient.h"

AQIClient::AQIClient()
{
    net = WiFiClientSecure();
    client = PubSubClient(net);
    lastTime = 0;
}

void AQIClient::begin()
{
    // Initialize the sensors
    bme680.begin();
    gps.begin();

    // Initialize WiFi and WiFiClient
    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.println(String("Attempting to connect to SSID: ") + String(WIFI_SSID));

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }

    Serial.println("Connected to the WiFi network");

    net.setCACert(AWS_CERT_CA);
    net.setCertificate(AWS_CERT_CRT);
    net.setPrivateKey(AWS_CERT_PRIVATE);

    // Connect to PubSubClient
    client.setServer(AWS_IOT_ENDPOINT, 8883);
    connect();

    // Generate a unique UUID for this instance of the AQIClient
    uint32_t seed1 = random(999999999);
    uint32_t seed2 = random(999999999);
    id.seed(seed1, seed2);
    id.generate();
}

void AQIClient::run()
{
    // Run sensors
    bme680.run();
    gps.run();

    if (!client.connected())
    { // Reconnect to PubSubClient if disconnected
        connect();
    }
    else
    {
        client.loop();
        if ((millis() - lastTime) > TIME_BETWEEN_PUBLISHES)
        { // Publish sensor data every 5 seconds
            lastTime = millis();
            publish();
        }
    }
}

void AQIClient::connect()
{
    Serial.println("Connecting to AWS IoT");

    while (!client.connect(THINGNAME))
    {
        delay(100);
        Serial.print(".");
    }

    if (!client.connected())
    {
        Serial.println("AWS IoT Timeout!");
        return;
    }

    Serial.println("AWS IoT Connected!");
}

void AQIClient::publish()
{
    JsonDocument doc;

    doc[ID] = id;

    BME680Data bme680Data = bme680.getData();
    doc[IAQ] = bme680Data.iaq;
    doc[CO2] = bme680Data.co2;
    doc[VOC] = bme680Data.voc;
    doc[TEMPERATURE] = bme680Data.temperature;
    doc[PRESSURE] = bme680Data.pressure;
    doc[HUMIDITY] = bme680Data.humidity;

    JsonObject location = doc[LOCATION].to<JsonObject>();
    GPSData gpsData = gps.getData();
    location[LATITUDE] = gpsData.lat;
    location[LONGITUDE] = gpsData.lng;

    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);
    Serial.println("Publishing: " + String(jsonBuffer));
    digitalWrite(LED_BUILTIN, HIGH);
    client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
}