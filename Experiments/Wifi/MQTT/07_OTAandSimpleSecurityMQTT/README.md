# OTA and Simple Security MQTT

Combines all previous features and adds OTA firmware updates and basic 
MQTT broker authentication.

## Hardware Used
- ESP32
- LED + Resistor
- Wires

## Libraries Included
```cpp
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
```

## Features
- **Broker:** Local Mosquitto (private)
- **Port:** 1883
- **Encryption:** None
- **Security:** Username/Password authentication
- **Retained Messages:** Yes (status + state change)
- **Non-Blocking:** Yes
- **Message Format:** JSON
- **LWT:** Yes
- **Heartbeat:** Every 5 seconds
- **Sensor Publishing:** Every 1 second
- **OTA Updates:** Yes

## Topics
| Topic | Direction | Purpose |
|---|---|---|
| `home/room1/esp32/led/cmd` | Subscribe | Receive JSON commands |
| `home/room1/esp32/led/state` | Publish | Report LED state as JSON |
| `home/room1/esp32/sensor` | Publish | Temperature and humidity data |
| `home/room1/esp32/status` | Publish | ONLINE/OFFLINE status |
| `home/room1/esp32/heartbeat` | Publish | Uptime and WiFi signal strength |

## How it Works
Brings together LED control, sensor publishing, LWT, heartbeat, and OTA into 
one sketch. MQTT connection now requires a username and password so only 
authorised clients can connect to the broker. OTA allows new firmware to be 
flashed wirelessly without removing the device.

## Setup
Replace with your broker credentials:
```cpp
client.connect("ESP32_Client_01", "YOUR_MQTT_USER", "YOUR_MQTT_PASSWORD", ...)
```

## Improvement Over SensorMosquitto
Adds two major production-ready features; **broker authentication** so the 
MQTT server is no longer open to anyone, and **OTA updates** so the device 
can be reprogrammed without physical access.