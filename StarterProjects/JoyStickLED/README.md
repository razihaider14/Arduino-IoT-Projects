# Joystick LED

Controls LED brightness using a joystick, with two brightness mapping 
modes toggled by the joystick button.

## Hardware Used
- Arduino
- Joystick Module
- LED + Resistor
- Wires

## How it Works
The joystick's X-axis controls LED brightness via PWM. Pressing the 
joystick button toggles between two mapping modes:

**Mode 1 (default):** Brightness maps to how far the joystick is from 
center in either direction — center is dim, full left or right is brightest.

**Mode 2:** Brightness maps inversely to distance from center — center 
is brightest, full left or right is dimmest.

## Pins
| Pin | Purpose |
|---|---|
| `A0` | Joystick X-axis |
| `7` | Joystick button |
| `10` | LED (PWM) |