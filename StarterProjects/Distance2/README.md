# Distance 2

Upgraded version of Distance1 — adds an LCD display to show the measured 
distance in real time.

## Hardware Used
- Arduino (Mega, due to high pin count)
- HC-SR04 Ultrasonic Sensor
- 16x2 LCD Display
- 4 Green LEDs + Resistors
- 4 Yellow LEDs + Resistors
- 4 Red LEDs + Resistors
- Buzzer
- Wires

## Libraries Included
```cpp
#include <LiquidCrystal.h>
```

## How it Works
Same proximity indication system as Distance1 — LEDs light up progressively 
and the buzzer activates in the red zone. The addition here is a 16x2 LCD 
that displays the live distance reading, showing cm for distances under 100cm 
and meters above that.

## Distance Zones
| Zone | Range | Indicator |
|---|---|---|
| Green | 125cm – 200cm | 1–4 green LEDs |
| Yellow | 40cm – 100cm | 1–4 yellow LEDs |
| Red + Buzz | ≤ 30cm | 1–4 red LEDs + buzzer |

## Improvement Over Distance1
Adds a **16x2 LCD display** for a real-time numerical distance readout 
instead of relying on Serial Monitor only.