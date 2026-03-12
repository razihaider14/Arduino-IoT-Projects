# LWT and Heartbeat

Adds Last Will Testament (LWT) and a heartbeat task to monitor ESP32 
availability and health over MQTT.

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
- **Retained Messages:** Yes (status topic)
- **Non-Blocking:** Yes
- **Message Format:** JSON
- **LWT:** Yes
- **Heartbeat:** Every 5 seconds

## Topics
| Topic | Direction | Purpose |
|---|---|---|
| `home/room1/esp32/led/cmd` | Subscribe | Receive JSON commands |
| `home/room1/esp32/led/state` | Publish | Report LED state as JSON |
| `home/room1/esp32/status` | Publish | ONLINE/OFFLINE status |
| `home/room1/esp32/heartbeat` | Publish | Uptime and WiFi signal strength |

## How it Works
When the ESP32 connects, it registers a **Last Will Testament** with the broker, so
if the device unexpectedly disconnects, the broker automatically publishes 
`OFFLINE` to the status topic. On successful connection it publishes `ONLINE`. 
Every 5 seconds a heartbeat message is sent containing uptime in seconds and 
WiFi signal strength (RSSI), so you can monitor the device's health remotely.

## Improvement Over MosquittoWorks
Adds device availability monitoring, so you can now tell from the broker whether 
the ESP32 is online, offline, and how healthy its connection is.