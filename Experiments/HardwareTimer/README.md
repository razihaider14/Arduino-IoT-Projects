# Hardware Timer

At a specific time, ```IRAM_ATTR``` is called and it pauses everything to execute what you want.

## Hardware Used
- Arduino / ESP32

## How it Works
Instead of using ```delay()``` or ```millis()```, we hard code to run a command at an accurate time. We setup the timer with very small ticks of about 1 ms, then we tell it to run a command after this many ticks.