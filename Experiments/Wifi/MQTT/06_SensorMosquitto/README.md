# Sensor Mosquitto

Adds simulated sensor data publishing to the existing MQTT LED control system.

## Hardware Used
- ESP32
- LED + Resistor
- Wires

## Libraries Included
```cpp
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
```

## Features
- **Broker:** Local Mosquitto (private)
- **Port:** 1883
- **Encryption:** None
- **Security:** None
- **Retained Messages:** Yes (on state change)
- **Non-Blocking:** Yes
- **Message Format:** JSON
- **Sensor Publishing:** Every 1 second

## Topics
| Topic | Direction | Purpose |
|---|---|---|
| `home/room1/esp32/led/cmd` | Subscribe | Receive JSON commands |
| `home/room1/esp32/led/state` | Publish | Report LED state as JSON |
| `home/room1/esp32/sensor` | Publish | Temperature and humidity data |

## How it Works
Every second, `taskSensor()` publishes simulated temperature (20.0–35.0°C) and 
humidity (40–80%) readings as JSON to the sensor topic. This was used to test 
the full data pipeline — MQTT broker → Node-RED → database — before connecting 
a real sensor.

## Note
Sensor data is randomly generated using `random()`. Replace `taskSensor()` with 
real sensor readings when connecting actual hardware like a DHT22 or BME280.

## Improvement Over LWTandHB
Introduces sensor data into the pipeline, making this the first project to 
simulate a real IoT data flow.