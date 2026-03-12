#include <LiquidCrystal.h>
int trigPin = 12;
int echoPin = 11;
int Time;
float Distance;
float distanceToTarget;
int rs = 48;
int en = 49;
int d4 = 50;
int d5 = 51;
int d6 = 52;
int d7 = 53;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int g1 = 22;
int g2 = 23;
int g3 = 24;
int g4 = 25;
int y1 = 26;
int y2 = 27;
int y3 = 28;
int y4 = 29;
int r1 = 30;
int r2 = 31;
int r3 = 32;
int r4 = 33;
int i;
int buzz = 34;

void setup() {
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(g1, OUTPUT);
  pinMode(g2, OUTPUT);
  pinMode(g3, OUTPUT);
  pinMode(g4, OUTPUT);
  pinMode(y1, OUTPUT);
  pinMode(y2, OUTPUT);
  pinMode(y3, OUTPUT);
  pinMode(y4, OUTPUT);
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  pinMode(buzz, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(10);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  Time = pulseIn(echoPin, HIGH);
  delay(25);
  Distance = (Time / 58);
  Serial.println(Distance);
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  if (Distance < 100.00) {
    lcd.print(Distance);
    lcd.print("cm");
  } else {
    lcd.print(Distance / 100.00);
    lcd.print("m");
  }
  delay(500);
  for (i = 22; i <= 33; i++) {
    digitalWrite(i, LOW);
  }
  digitalWrite(buzz, LOW);
  if (Distance <= 200) {
    digitalWrite(g1, HIGH);
  }
  if (Distance <= 175) {
    digitalWrite(g2, HIGH);
  }
  if (Distance <= 150) {
    digitalWrite(g3, HIGH);
  }
  if (Distance <= 125) {
    digitalWrite(g4, HIGH);
  }
  if (Distance <= 100) {
    digitalWrite(y1, HIGH);
  }
  if (Distance <= 80) {
    digitalWrite(y2, HIGH);
  }
  if (Distance <= 60) {
    digitalWrite(y3, HIGH);
  }
  if (Distance <= 40) {
    digitalWrite(y4, HIGH);
  }
  if (Distance <= 30) {
    digitalWrite(r1, HIGH);
    digitalWrite(buzz, HIGH);
  }
  if (Distance <= 20) {
    digitalWrite(r2, HIGH);
    digitalWrite(buzz, HIGH);
  }
  if (Distance <= 10) {
    digitalWrite(r3, HIGH);
    digitalWrite(buzz, HIGH);
  }
  if (Distance <= 5) {
    digitalWrite(r4, HIGH);
    digitalWrite(buzz, HIGH);
  }
}