# Distance 1

A proximity indicator using an ultrasonic sensor, 12 LEDs, and a buzzer 
to show how close an object is.

## Hardware Used
- Arduino (Mega, due to high pin count)
- HC-SR04 Ultrasonic Sensor
- 4 Green LEDs + Resistors
- 4 Yellow LEDs + Resistors
- 4 Red LEDs + Resistors
- Buzzer
- Wires

## How it Works
The ultrasonic sensor measures distance and lights up LEDs progressively 
as an object gets closer — green LEDs turn on first, then yellow, then red. 
The buzzer activates when the object enters the red zone (≤30cm). Distance 
is also printed to Serial Monitor in cm or meters depending on range.

## Distance Zones
| Zone | Range | Indicator |
|---|---|---|
| Green | 125cm – 200cm | 1–4 green LEDs |
| Yellow | 40cm – 100cm | 1–4 yellow LEDs |
| Red + Buzz | ≤ 30cm | 1–4 red LEDs + buzzer |
| Too Close | < 2cm | Serial warning only |