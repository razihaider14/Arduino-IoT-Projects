#include <DHT.h>
#define DHTPIN A5
#define Type DHT11
int green = 11;
int relay = 3;
float temp;
DHT dht(DHTPIN, Type);

void setup() {
  // put your setup code here, to run once:
pinMode(green, OUTPUT);
pinMode(relay, OUTPUT);
Serial.begin(9600);
dht.begin();

}

void loop() {
  // put your main code here, to run repeatedly:
temp = dht.readTemperature();
if (temp >= 27.50 ){
  digitalWrite(relay,HIGH);
  digitalWrite(green, LOW);
  Serial.println("Temp: " + String(temp));
  Serial.println("Fire Alert");
}
else {
  digitalWrite(green,HIGH);
  digitalWrite(relay, LOW);
  Serial.println("Temp: " + String(temp));
  Serial.println("Green ON");
}
delay(500);
}
