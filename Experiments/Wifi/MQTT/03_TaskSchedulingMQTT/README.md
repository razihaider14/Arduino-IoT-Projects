# Task Scheduling MQTT

MQTT LED control with JSON messaging and a timed publish task running alongside 
the main loop.

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
- **Broker:** broker.hivemq.com (public)
- **Port:** 1883
- **Encryption:** None
- **Security:** None
- **Retained Messages:** No
- **Non-Blocking:** Yes
- **Message Format:** JSON

## Topics
| Topic | Direction | Purpose |
|---|---|---|
| `home/room1/esp32/led/cmd` | Subscribe | Receive JSON commands |
| `home/room1/esp32/led/state` | Publish | Report LED state as JSON |

## How it Works
Commands arrive as JSON instead of plain text — `{"led":"ON"}` or `{"led":"OFF"}`.
The publish interval can also be changed remotely by sending `{"interval":3000}` 
(value in milliseconds). A non-blocking timer task publishes the LED state 
periodically without using `delay()` or blocking the loop.

## Improvement Over nonblockingmqtt
Introduces JSON messaging and a scheduled task pattern — instead of only reacting 
to incoming commands, the ESP32 also proactively reports its state at a set interval.