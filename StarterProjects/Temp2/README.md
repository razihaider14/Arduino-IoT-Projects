# Temp 2

Reads temperature from a DHT11 sensor and triggers a relay and status 
LED based on a temperature threshold.

## Hardware Used
- Arduino
- DHT11 Temperature Sensor
- Relay Module
- Green LED + Resistor
- Wires

## Libraries Included
```cpp
#include <DHT.h>
```

## How it Works
Temperature is read every 500ms. If it reaches or exceeds 27.5°C the 
relay activates and the green LED turns OFF, simulating a fire alert 
or fan/cooling trigger. Below the threshold the relay is OFF and the 
green LED stays ON indicating normal conditions.

## Pins
| Pin | Purpose |
|---|---|
| `A5` | DHT11 data pin |
| `11` | Green LED |
| `3` | Relay |

## Improvement Over Temp
Adds a **relay output** to actually control external hardware based on 
temperature, making it a practical automatic trigger instead of just 
a monitor.