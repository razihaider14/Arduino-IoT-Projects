# Simple WiFi Server

ESP32 connects to existing WiFi and hosts a web server to control a yellow LED 
from a browser.

## Hardware Used
- ESP32
- Red, Green, Yellow LEDs + Resistors
- Wires

## Libraries Included
```cpp
#include <WiFi.h>
```

## How it Works
The ESP32 connects to WiFi. The red LED blinks during the connection and turns OFF 
once connected, green LED turns ON to confirm. It then hosts a basic webpage on 
its local IP with two links to turn the yellow LED ON or OFF.

## Setup
Replace credentials before uploading:
```cpp
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
```
After uploading, check Serial Monitor for the ESP32's IP address and open it in 
a browser.

## Difference from AccessPoint
Unlike the AccessPoint project, this one connects to your **existing WiFi network** 
rather than creating its own.