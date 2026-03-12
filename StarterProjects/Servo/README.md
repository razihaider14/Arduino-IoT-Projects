# Servo

Controls a servo motor position using a joystick.

## Hardware Used
- Arduino
- Servo Motor
- Joystick Module
- Wires

## Libraries Included
```cpp
#include <Servo.h>
```

## How it Works
The joystick's X-axis analog value (0–1023) is mapped to a servo angle 
(0°–180°). Moving the joystick smoothly rotates the servo to the 
corresponding position. Both joystick and servo values are printed 
to Serial Monitor in real time.

## Pins
| Pin | Purpose |
|---|---|
| `A0` | Joystick X-axis |
| `3` | Servo signal |