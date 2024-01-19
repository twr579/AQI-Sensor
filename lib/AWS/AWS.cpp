/**
 * AWS.cpp - AWS library routines
 */

#include "AWS.h"

WiFiClientSecure net = WiFiClientSecure();
PubSubClient client(net);
long lastMsg = 0;
bool ledState = LOW;

void setupAWS()
{
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

    client.setServer(AWS_IOT_ENDPOINT, 8883);
    connectAWS();
}

void connectAWS()
{
    Serial.println("Connecting to AWS IOT");

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

void publish(JsonDocument &doc)
{
    if (!client.connected())
    {
        connectAWS();
    }
    else
    {
        client.loop();
        if (millis() - lastMsg > 5000)
        {
            lastMsg = millis();
            char jsonBuffer[512];
            serializeJson(doc, jsonBuffer);
            Serial.println("Publishing: " + String(jsonBuffer));
            ledState = ledState == LOW ? HIGH : LOW;
            digitalWrite(LED_BUILTIN, ledState);
            client.publish(AWS_IOT_PUBLISH_TOPIC, jsonBuffer);
        }
    }
}