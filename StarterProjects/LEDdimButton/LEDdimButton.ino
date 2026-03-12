

int ledPin = 11;
int ledVal = 0;
int S1;
int S1pin = 5;
int S2;
int S2pin = 3;
int dt = 100;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(S1pin, INPUT);
  digitalWrite(S1pin, HIGH);
  pinMode(S2pin, INPUT);
  digitalWrite(S2pin, HIGH);
  Serial.begin(9600);
}
void loop() {
  // put your main code here, to run repeatedly:

  S1 = digitalRead(S1pin);
  S2 = digitalRead(S2pin);
  if(S1 == 0){
    ledVal = ledVal + 10;
  }
  if(S2 == 0){
    ledVal = ledVal - 10;
  }
  if(ledVal < 0){
    ledVal = 0;
  }
  if(ledVal > 255){
    ledVal = 255;
  }

  analogWrite(ledPin, ledVal);
  Serial.print(S1);
  Serial.print(",");
  Serial.print(S2);
  Serial.print(",");
  Serial.println(ledVal);



  delay(dt);
}
