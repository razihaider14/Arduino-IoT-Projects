#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

const int ledPins[] = {13, 12, 14, 26, 25, 32};
const int ledCount = 6;

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  SerialBT.begin("ESP32-Mobile");
}

void loop() {
  if (SerialBT.available()) {
    String com = SerialBT.readStringUntil('\n');
    com.trim();

    int ledNumber = com.charAt(0) - '0'; 
    String state = com.substring(2);      

    if (ledNumber >= 1 && ledNumber <= ledCount) {
      int pin = ledPins[ledNumber - 1];

      if (state == "ON") {
        digitalWrite(pin, HIGH);
        SerialBT.println("LED " + String(ledNumber) + " ON");
      }
      else if (state == "OFF") {
        digitalWrite(pin, LOW);
        SerialBT.println("LED " + String(ledNumber) + " OFF");
      }
    }
    else {
      SerialBT.println("Invalid LED number");
    }
  }
}


