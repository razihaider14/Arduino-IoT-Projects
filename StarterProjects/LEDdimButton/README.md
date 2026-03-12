# LED Dim Button

Controls LED brightness using two push buttons — one to increase 
brightness and one to decrease it.

## Hardware Used
- Arduino
- 2 Push Buttons
- LED + Resistor
- Wires

## How it Works
Pressing S1 increases brightness by 10 steps, pressing S2 decreases 
it by 10 steps. Brightness is clamped between 0 and 255 so it never 
overflows. Current button states and brightness value are printed to 
Serial Monitor in real time.

## Pins
| Pin | Purpose |
|---|---|
| `5` | S1 — brightness up |
| `3` | S2 — brightness down |
| `11` | LED (PWM) |