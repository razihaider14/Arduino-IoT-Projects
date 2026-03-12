#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "*******";
const char* password = "******";

const char* mqtt_server = "ip";
const int mqtt_port = 1883;

const char* led_cmd_topic = "home/room1/esp32/led/cmd";
const char* led_state_topic = "home/room1/esp32/led/state";
const char* sensor_topic = "home/room1/esp32/sensor";

const int ledPin = 19;

WiFiClient espClient;
PubSubClient client(espClient);

bool ledState = false;

void callback(char* topic, byte* payload, unsigned int length) {

  StaticJsonDocument<128> doc;

  DeserializationError err = deserializeJson(doc, payload, length);

  if (err) return;   // invalid JSON

  // read LED
  if (doc["led"]) {
    const char* ledCmd = doc["led"];

    if (strcmp(ledCmd, "ON") == 0) {
      ledState = true;
      stateChange();
    }
    if (strcmp(ledCmd, "OFF") == 0) {
      ledState = false;
      stateChange();
    }
  }
}


unsigned long lastWifiAttempt = 0;
void handleWiFi() {
  if (WiFi.status() == WL_CONNECTED) return;

  if (millis() - lastWifiAttempt > 5000) {
    lastWifiAttempt = millis();
    WiFi.begin(ssid, password);
  }
}

unsigned long lastMqttAttempt = 0;
void handleMQTT() {
  if (WiFi.status() != WL_CONNECTED) return;

  if (!client.connected()) {
    if (millis() - lastMqttAttempt > 2000) {
      lastMqttAttempt = millis();

      if (client.connect("ESP32_Client_01")) {
        Serial.println("MQTT connected");
        client.subscribe(led_cmd_topic);
      } 
      else {
        Serial.print("MQTT failed, rc=");
        Serial.println(client.state());
      }
    }
  }
}

void handleIO() {
  digitalWrite(ledPin, ledState);
}

unsigned long tPublish = 0;
void taskPublish() {
  if (millis() - tPublish >= 3000) {
    tPublish = millis();

    const char* ledStatestr = ledState ? "ON" : "OFF";

    char msg[64];

    snprintf(msg, sizeof(msg),"{\"led\":\"%s\"}",ledStatestr);

    client.publish(led_state_topic, msg);
  }
}

void stateChange() {
  const char* s = ledState ? "ON" : "OFF";
  char msg[32];
  snprintf(msg, sizeof(msg), "{\"led\":\"%s\"}", s);
  client.publish(led_state_topic, msg, true); // retained
}

unsigned long tSensor = 0;
void taskSensor() {
  if (millis() - tSensor >= 1000) {   // every 1s
    tSensor = millis();

    float temp = random(200, 350) / 10.0;   // 20.0–35.0 °C
    int hum = random(40, 80);               // 40–80 %

    char msg[64];
    snprintf(msg, sizeof(msg), "{\"temp\":%.1f,\"hum\":%d}", temp, hum);

    client.publish(sensor_topic, msg);
  }
}

void setup() {
  Serial.begin(115200);
  randomSeed(micros());
  pinMode(ledPin, OUTPUT);
  handleWiFi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  handleMQTT();
}

void loop() {
  handleWiFi();
  handleMQTT();
  client.loop();
  handleIO();
  taskPublish();
  taskSensor();
}

