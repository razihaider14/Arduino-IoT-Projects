#include <DHT11.h>


#define Type DHT11
int sensePin = A3;
float temp;
DHT11 T(sensePin);
int dt = 100;


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); 

}

void loop() {
  // put your main code here, to run repeatedly:
temp = T.readTemperature();

if (temp >70){
  Serial.print("OverHeat/n");
}
else{
  Serial.print("Normal Temp");
  Serial.println("");
}

Serial.print("Temp = " );
Serial.print(temp);
Serial.println("C");
delay(dt);
}
