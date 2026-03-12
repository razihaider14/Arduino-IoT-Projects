# Mosquitto Works

Same as TaskSchedulingMQTT but switched from a public broker to a 
local Mosquitto broker running on a private server.

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

## Topics
| Topic | Direction | Purpose |
|---|---|---|
| `home/room1/esp32/led/cmd` | Subscribe | Receive JSON commands |
| `home/room1/esp32/led/state` | Publish | Report LED state as JSON |

## How it Works
Works the same as TaskSchedulingMQTT with one addition — `stateChange()` 
immediately publishes a retained message the moment the LED state changes, 
instead of waiting for the next scheduled publish interval. This means any 
new client connecting to the broker instantly gets the current LED state.

## Setup
Replace with your local Mosquitto broker's IP:
```cpp
const char* mqtt_server = "YOUR_BROKER_IP";
```

## Improvement Over TaskSchedulingMQTT
Moves from a public broker to a **local Mosquitto broker** for private 
communication, and adds instant retained publishing on state change.