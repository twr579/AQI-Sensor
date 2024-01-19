/**
 * AWS.cpp - AWS library routines
 */

#include "secrets.h"
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#define AWS_IOT_PUBLISH_TOPIC "esp32/pub"

// Connects to WiFi and establishes connection with AWS IoT thing
void setupAWS();

// Connects PubSubClient to AWS IoT thing
void connectAWS();

/**
 * Publishes JsonDocument to AWS IoT Core
 *
 * @param doc a reference to a JsonDocument to publish to AWS IoT
 */
void publish(JsonDocument &doc);