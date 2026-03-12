# MQTT Projects

A series of MQTT projects built on ESP32, progressively adding features from 
a basic connection all the way to a fully encrypted production-ready system.

## Progression

| # | Project | Key Addition |
|---|---|---|
| 1 | `simplemqtt` | Basic MQTT LED control |
| 2 | `nonblockingmqtt` | Non-blocking state machine reconnection |
| 3 | `TaskSchedulingMQTT` | JSON messaging + scheduled publishing |
| 4 | `MosquittoWorks` | Switched to local Mosquitto broker |
| 5 | `LWTandHB` | Last Will Testament + heartbeat monitoring |
| 6 | `SensorMosquitto` | Simulated sensor data publishing |
| 7 | `OTAandSimpleSecurityMQTT` | OTA updates + broker authentication |
| 8 | `Complete` | Full TLS encryption — final form |

## What is MQTT?
MQTT is a lightweight messaging protocol designed for IoT devices. It works 
on a publish/subscribe model — devices publish messages to topics and 
subscribe to topics to receive messages, all through a central broker.

## Broker
Early projects use **HiveMQ** (public broker) for simplicity. From 
`MosquittoWorks` onward, a **local Mosquitto broker** is used for 
private communication.

## Final System Features
By `Complete`, the full system includes:
- TLS encrypted connection on port 8883
- Username/Password broker authentication
- CA certificate verification
- Last Will Testament for disconnect detection
- Heartbeat publishing every 5 seconds
- Sensor data publishing every 1 second
- OTA firmware updates over WiFi
- Non-blocking WiFi and MQTT reconnection
- JSON messaging throughout

## Dependencies
Install these libraries from Arduino Library Manager:
- **PubSubClient** by Nick O'Leary
- **ArduinoJson** by Benoit Blanchon
- **ArduinoOTA** (built into ESP32 board package)