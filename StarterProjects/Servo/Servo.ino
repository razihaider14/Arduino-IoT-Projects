
#include <Servo.h>

Servo myServo;
int servoPin = 3;
int joystickPin = A0;
int joystickVal;
int servoVal;

void setup() {
  // put your setup code here, to run once:
  pinMode(joystickPin, INPUT);
  pinMode(servoPin, OUTPUT);
myServo.attach(servoPin);
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
joystickVal = analogRead(joystickPin);
servoVal = (180./1023.)*joystickVal;
myServo.write(servoVal);

Serial.print(joystickVal);
Serial.print(",");
Serial.println(servoVal);



}
