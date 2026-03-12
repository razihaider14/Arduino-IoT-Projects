# Complete

Full production-ready MQTT system with TLS encryption, OTA updates, broker 
authentication, sensor publishing, LWT, and heartbeat; all in one sketch.

## Hardware Used
- ESP32
- LED + Resistor
- Wires

## Libraries Included
```cpp
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <ArduinoOTA.h>
```

## Features
- **Broker:** Local Mosquitto (private)
- **Port:** 8883
- **Encryption:** TLS (SSL)
- **Security:** Username/Password + CA Certificate verification
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
| `home/esp32/cmd` | Subscribe | Receive JSON commands |
| `home/esp32/state` | Publish | Report LED state as JSON |
| `home/esp32/sensor` | Publish | Temperature and humidity data |
| `home/esp32/status` | Publish | ONLINE/OFFLINE status |
| `home/esp32/heartbeat` | Publish | Uptime and WiFi signal strength |

## How it Works
Same as OTAandSimpleSecurityMQTT but the connection is now fully encrypted 
using TLS on port 8883. The ESP32 verifies the broker's identity using a 
CA certificate before connecting, preventing man-in-the-middle attacks. 
`WiFiClientSecure` is used instead of `WiFiClient` to handle the encrypted 
connection.

## Setup
Replace with your broker's IP and credentials:
```cpp
const char* mqtt_server = "YOUR_BROKER_IP";
client.connect("ESP32_Client_01", "YOUR_MQTT_USER", "YOUR_MQTT_PASSWORD", ...)
```
Also replace `ca_cert` with the CA certificate generated for your own 
Mosquitto broker.

## Improvement Over OTAandSimpleSecurityMQTT
Upgrades the connection from plain text to **fully encrypted TLS** — the 
most secure setup in this series.