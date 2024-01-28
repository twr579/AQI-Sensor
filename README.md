# AQI Sensor
A compact, portable sensor intended to measure and store a history of Air Quality Index (AQI) readings while on the go. Developed in the PlatformIO IDE for VS Code on an ESP32 microcontroller (Adafruit HUZZAH32).

## Hardware Diagram
![Screenshot 2024-01-27 174706](https://github.com/twr579/AQI-Sensor/assets/55030795/22156916-bc2e-4738-81e4-be9c33c77968)

In addition to the microcontroller, hardware components include a BME680 sensor, a NEO-6M GPS module (w/ antenna), a 3.7V LiPo battery, and a slide switch with center pin connected to the GND pin of the microcontroller and an outer pin connected to the EN pin, allowing the system to be toggled on/off.

## How It Works
On powering the microcontroller, the sensor enters an initialization stage. This includes establishing a WiFi connection (I connect to the hotspot on my iPhone), waiting for the BME680 sensor to calibrate to its environment (~5 min) and the GPS module to find a fix (<1 min), and connecting the PubSubClient to AWS IoT Core. Once setup is complete, the loop gets the most recent data (AQI, VOC level, CO2 level, temperature, pressure, humidity, coordinates) from the BME680 and GPS module and publishes that data to an AWS IoT publish topic (I called mine 'esp32/pub') every 30 seconds via an MQTT message.

![Screenshot 2024-01-28 125821](https://github.com/twr579/AQI-Sensor/assets/55030795/205a115e-e857-4bdb-895a-a4602690caf3)

The MQTT message arrives at the IoT Core Thing whose endpoint, certificate, and private key are provided in the "secrets.h" file and which has a rule on the pub topic. This rule triggers an action that inserts the data into a DynamoDB table, which you can then display in a web app however you'd like.
