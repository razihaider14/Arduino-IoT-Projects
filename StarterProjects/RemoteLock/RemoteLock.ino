#include <LiquidCrystal_I2C.h>
#include <IRremote.hpp>

const int IRpin = 9;
int redPin = 8;
int greenPin = 7;
int buzzPin = 6;
String myResults;
String entered = "";
int failures = 0;
const String Password = "1234";
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

void setup() {
  //put your setup code here, to run once:
  Serial.begin(9600);
  IrReceiver.begin(IRpin);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(buzzPin, OUTPUT);
  lcd.begin(16,2);
  lcd.backlight(); 
  //digitalWrite(greenPin, LOW);
  //digitalWrite(redPin, LOW);
  //noTone(buzzPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (IrReceiver.decode()) {
    //Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
    String myResults = "";  

    if (IrReceiver.decodedIRData.decodedRawData == 0xE916FF00) {
      myResults = "zero";
      //Serial.println(myResults);
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xF30CFF00) {
      myResults = "one";
      //Serial.println(myResults);
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xE718FF00) {
      myResults = "two";
      //Serial.println(myResults);
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xA15EFF00) {
      myResults = "three";
      //Serial.println(myResults);
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xF708FF00) {
      myResults = "four";
      //Serial.println(myResults);
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xE31CFF00) {
      myResults = "five";
      //Serial.println(myResults);
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xA55AFF00) {
      myResults = "six";
      //Serial.println(myResults);
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xBD42FF00) {
      myResults = "seven";
      //Serial.println(myResults);
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xAD52FF00) {
      myResults = "eight";
      //Serial.println(myResults);
    }
    if (IrReceiver.decodedIRData.decodedRawData == 0xB54AFF00) {
      myResults = "nine";
      //Serial.println(myResults);
    }
    if (myResults == "zero") {
      entered += "0";
    }
    if (myResults == "one") {
      entered += "1";
    }
    if (myResults == "two") {
      entered += "2";
    }
    if (myResults == "three") {
      entered += "3";
    }
    if (myResults == "four") {
      entered += "4";
    }
    if (myResults == "five") {
      entered += "5";
    }
    if (myResults == "six") {
      entered += "6";
    }
    if (myResults == "seven") {
      entered += "7";
    }
    if (myResults == "eight") {
      entered += "8";
    }
    if (myResults == "nine") {
      entered += "9";
    }

    if (myResults != "") {
      lcd.setCursor(0,0);
      lcd.print("Entered so far: ");
      lcd.setCursor(0,1);
      lcd.print(entered);
      Serial.print("Entered so far: ");
      Serial.println(entered);
      delay(200);
    }

    if (entered.length() >= 4) {
      if (entered == Password) {
        digitalWrite(greenPin, HIGH);
        digitalWrite(redPin, LOW);
        failures = 0;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("CORRECT!");
        Serial.println("CORRECT!");
        delay(2000);
      } else {
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
        failures++;
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("WRONG");
        lcd.setCursor(0,1);
        lcd.print("Access Denied");
        Serial.println("WRONG");
        if(failures >= 5) {
          delay(500);
        }
        else {
          delay(2000);
        }
        digitalWrite(redPin, LOW);
      }

      if (failures >= 5) {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("5 FAILURES!");
        Serial.println("5 FAILURES!");
        digitalWrite(buzzPin, HIGH);; delay(500);
        digitalWrite(buzzPin, LOW);;
        failures = 0;
      }

      entered = "";
      digitalWrite(greenPin, LOW);
      lcd.clear();
    }
    IrReceiver.resume();
  }
}