int g1 = 42;
int g2 = 43;
int g3 = 44; 
int g4 = 45;
int y1 = 46; 
int y2 = 47;
int y3 = 48;
int y4 = 49;
int r1 = 50;
int r2 = 51;
int r3 = 52;
int r4 = 53;
int buzz = 31;
int trig = 7;
int echo = 8;
int distance;
int time;
int i;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(g1,OUTPUT);
pinMode(g2,OUTPUT);
pinMode(g3,OUTPUT);
pinMode(g4,OUTPUT);
pinMode(y1,OUTPUT);
pinMode(y2,OUTPUT);
pinMode(y3,OUTPUT);
pinMode(y4,OUTPUT);
pinMode(r1,OUTPUT);
pinMode(r2,OUTPUT);
pinMode(r3,OUTPUT);
pinMode(r4,OUTPUT);
pinMode(buzz,OUTPUT);
pinMode(trig,OUTPUT);
pinMode(echo,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(trig,LOW);
delayMicroseconds(10);
digitalWrite(trig,HIGH);
delayMicroseconds(10);
digitalWrite(trig,LOW);
time = pulseIn(echo,HIGH);
distance = time/58.00;
delay(25);
if(distance < 100.00 && distance >= 2.00){
  Serial.print(distance);
  Serial.println("cm");
}
else if(distance >= 100.00){
  Serial.print(distance/100.00);
  Serial.println("m");
}
else if(distance < 2.00){
  Serial.println("TOO CLOSE");
}
for (i=42;i<=53;i++){
  digitalWrite(i,LOW);
}
digitalWrite(buzz,LOW);
if(distance <= 200.00){
  digitalWrite(g1,HIGH);
}
if(distance <= 175.00){
  digitalWrite(g2,HIGH);
}
if(distance <= 150.00){
  digitalWrite(g3,HIGH);
}
if(distance <= 125.00){
  digitalWrite(g4,HIGH);
}
if(distance <= 100.00){
  digitalWrite(y1,HIGH);
}
if(distance <= 80.00){
  digitalWrite(y2,HIGH);
}
if(distance <= 60.00){
  digitalWrite(y3,HIGH);
}
if(distance <= 40.00){
  digitalWrite(y4,HIGH);
}
if(distance <= 30.00){
  digitalWrite(r1,HIGH);
  digitalWrite(buzz,HIGH);
}
if(distance <= 20.00){
  digitalWrite(r2,HIGH);
  digitalWrite(buzz,HIGH);
}
if(distance <= 10.00){
  digitalWrite(r3,HIGH);
  digitalWrite(buzz,HIGH);
}
if(distance <= 5.00){
  digitalWrite(r4,HIGH);
  digitalWrite(buzz,HIGH);
}

delay(100);



}
