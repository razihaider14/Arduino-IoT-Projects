# Non-Blocking MQTT

MQTT LED control with non-blocking WiFi/MQTT reconnection using a state machine.

## Hardware Used
- ESP32
- 3 LEDs + Resistors (Main, WiFi Status, MQTT Status)
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
- **Non-Blocking:** Yes — no `while()` loops waiting for connection

## Topics
| Topic | Direction | Purpose |
|---|---|---|
| `home/room1/esp32/led/cmd` | Subscribe | Receive ON/OFF commands |
| `home/room1/esp32/led/state` | Publish | Report current LED state |

## How it Works
Instead of blocking the program while connecting, a state machine cycles through 
three states — `CONNECTING_WIFI` → `CONNECTING_MQTT` → `RUNNING`. Two status LEDs 
blink to show WiFi and MQTT connection progress. If either connection drops, the 
state machine automatically falls back and reconnects without freezing the program.

## Improvement Over simplemqtt
`simplemqtt` uses blocking `while()` loops to connect — if connection fails, the 
entire program freezes. This version handles everything non-blocking so the board 
stays responsive at all times.