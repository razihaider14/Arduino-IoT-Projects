const int buttonPin = 4;
const int ledPin = 18;

volatile bool buttonEvent = false;
volatile int buttonCount = 0;

bool ledState = false;

unsigned long lastPressTime = 0;

void IRAM_ATTR handleButton() {
  buttonEvent = true;
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

  attachInterrupt(buttonPin, handleButton, FALLING);
}

void loop() {

  if (buttonEvent) {
    buttonEvent = false;

    if (millis() - lastPressTime > 250) {
      buttonCount++;
      ledState = !ledState;
      Serial.println(buttonCount);
      lastPressTime = millis();
    }
  }
  digitalWrite(ledPin, ledState);
}

