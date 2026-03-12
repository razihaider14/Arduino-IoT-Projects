const int ledPin = 10;
const int joyStickPinX = A0;
const int buttonPin = 7;
int ledValue;

bool buttonState = false;
int buttonEvent;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  pinMode(buttonPin,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
int  jValue = analogRead(joyStickPinX);

  if (!buttonState) {
    ledValue = abs(map(jValue, 0, 1023, -255, 255));
  }
  else {
    int jValue2 = abs(jValue - 512);
    ledValue = map(jValue2, 0, 512, 255, 0);
  }

  buttonEvent = digitalRead(buttonPin);

  if (buttonEvent == 0) {
    buttonState = !buttonState;
  }

  analogWrite(ledPin,ledValue);

  delay(200);
}
