# Bluetooth

Controlling a series of LEDs via bluetooth.

## Hardware Used
- ESP32
- 6 LEDs + Resistors
- Wires

## Libraries Included
```cpp
#include <BluetoothSerial.h>
```

## Commands 
Numbers from **1** to **6** and ***ON*** or ***OFF***.

## How it Works
The command from bluetooth is analysed and the corresponding LED is turned ON or OFF according to the command.