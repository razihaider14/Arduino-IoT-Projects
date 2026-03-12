# Interrupt Servive Routine

When button is pressed, it immediately gets noticed.

## Hardware Used
- Arduino / ESP32
- Push Button 
- LED + Resistor
- Wires

## How it Works
The moment the button is pressed, ``` handleButton() ``` gets called which runs ```IRAM_ATTR ```, so every other process is paused and ```buttonEvent``` becomes true, so in the next moment, the LED turns ON.