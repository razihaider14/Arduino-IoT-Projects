# Simple OTA

Update ESP32 firmware wirelessly over WiFi without needing a USB cable.

## Hardware Used
- ESP32
- LED + Resistor
- Wires

## Libraries Included
```cpp
#include <WiFi.h>
#include <ArduinoOTA.h>
```

## How it Works
The ESP32 connects to WiFi and starts listening for OTA updates. The LED blinks 
every second just to confirm the board is running. When you upload new code from 
Arduino IDE over the network, `ArduinoOTA.handle()` catches it and flashes the 
new firmware.

## Setup
Replace credentials before uploading:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```
OTA password is set to `"1234"` — change it to something stronger if needed.

## Note
Make sure your PC and ESP32 are on the same WiFi network when uploading OTA.
The board will appear as **esp32-room1** in Arduino IDE under network ports.