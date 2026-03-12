#include <WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "*****";
const char* password = "*****";

const int ledPin = 19;

unsigned long t = 0;
bool state = false;

void setup() {
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  Serial.println(WiFi.localIP());

  ArduinoOTA.setHostname("esp32-room1");
  ArduinoOTA.setPassword("1234");

  ArduinoOTA.begin();
}

void loop() {
  ArduinoOTA.handle(); 

  if (millis() - t > 1000) {
    t = millis();
    state = !state;
    digitalWrite(ledPin, state);
  }
}
