#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "*****";
const char* password = "*****";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* led_cmd_topic = "home/room1/esp32/led/cmd";
const char* led_state_topic = "home/room1/esp32/led/state";

const int ledPin = 19;

WiFiClient espClient;
PubSubClient client(espClient);

bool ledState = false;

unsigned long publishInterval = 5000;

void callback(char* topic, byte* payload, unsigned int length) {

  StaticJsonDocument<128> doc;

  DeserializationError err = deserializeJson(doc, payload, length);

  if (err) return;   // invalid JSON

  // read LED
  if (doc["led"]) {
    const char* ledCmd = doc["led"];

    if (strcmp(ledCmd, "ON") == 0)  ledState = true;
    if (strcmp(ledCmd, "OFF") == 0) ledState = false;
  }

  // read interval
  if (doc["interval"]) {
    publishInterval = doc["interval"];
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
        client.subscribe(led_cmd_topic);
      }
    }
  }
}

void handleIO() {
  digitalWrite(ledPin, ledState);
}

unsigned long tPublish = 0;
void taskPublish() {
  if (millis() - tPublish >= publishInterval) {
    tPublish = millis();

    const char* ledStatestr = ledState ? "ON" : "OFF";

    char msg[64];

    snprintf(msg, sizeof(msg),"{\"led\":\"%s\"}",ledStatestr);

    client.publish(led_state_topic, msg);
  }
}


void setup() {
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
}