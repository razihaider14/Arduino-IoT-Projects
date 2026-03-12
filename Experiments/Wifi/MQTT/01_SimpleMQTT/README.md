# Simple MQTT

Basic MQTT communication over WiFi to control an LED remotely using publish/subscribe.

## Hardware Used
- ESP32
- LED + Resistor
- Wires

## Libraries Included
```cpp
#include <WiFi.h>
#include <PubSubClient.h>
```

## Features
- **Broker:** broker.hivemq.com (public)
- **Port:** 1883
- **Encryption:** None
- **Security:** None
- **Retained Messages:** Yes

## Topics
| Topic | Direction | Purpose |
|---|---|---|
| `home/room1/esp32/led/cmd` | Subscribe | Receive ON/OFF commands |
| `home/room1/esp32/led/state` | Publish | Report current LED state |

## How it Works
The ESP32 connects to WiFi and then to a public MQTT broker. It subscribes to a 
command topic and listens for `ON` or `OFF` messages. When a message arrives, it 
turns the LED accordingly and publishes the new state back to the state topic.