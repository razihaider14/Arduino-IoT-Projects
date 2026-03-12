# Temp

Reads temperature from a DHT11 sensor and prints it to Serial Monitor 
with an overheat warning.

## Hardware Used
- Arduino
- DHT11 Temperature Sensor
- Wires

## Libraries Included
```cpp
#include <DHT11.h>
```

## How it Works
Reads temperature every 100ms and prints it to Serial Monitor. If the 
temperature exceeds 70°C an overheat warning is printed, otherwise it 
reports normal temperature.

## Pins
| Pin | Purpose |
|---|---|
| `A3` | DHT11 data pin |