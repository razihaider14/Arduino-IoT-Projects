# Access Point

ESP32 acts as a WiFi Access Point and hosts a web server to control an LED from a browser.

## Hardware Used
- ESP32
- LED + Resistor
- Wires

## Libraries Included
```cpp
#include <WiFi.h>
#include <WebServer.h>
```

## How it Works
The ESP32 creates its own WiFi network and hosts a simple webpage on `192.168.1.1`. 
When you connect to the ESP32's WiFi and open that IP in a browser, you get a page 
with buttons to turn the LED ON or OFF.

## Setup
Replace these with your preferred credentials before uploading:
```cpp
const char* ssid = "YOUR_AP_NAME";
const char* pass = "YOUR_AP_PASSWORD";
```