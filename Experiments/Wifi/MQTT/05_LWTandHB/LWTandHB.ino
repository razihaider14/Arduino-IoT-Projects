#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "*****";
const char* password = "******";

const char* mqtt_server = "ip";
const int mqtt_port = 1883;

const char* led_cmd_topic = "home/room1/esp32/led/cmd";
const char* led_state_topic = "home/room1/esp32/led/state";
const char* status_topic = "home/room1/esp32/status";
const char* heartbeat_topic = "home/room1/esp32/heartbeat";

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

    if (strcmp(ledCmd, "ON") == 0)  ledState = true;
    if (strcmp(ledCmd, "OFF") == 0) ledState = false;
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

      if (client.connect("ESP32_Client_01",status_topic , 0 , true , "OFFLINE")) {
        Serial.println("MQTT connected");
        client.subscribe(led_cmd_topic);
        client.publish(status_topic, "ONLINE", true);
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
  if (millis() - tPublish >= 2000) {
    tPublish = millis();

    const char* ledStatestr = ledState ? "ON" : "OFF";

    char msg[64];

    snprintf(msg, sizeof(msg),"{\"led\":\"%s\"}",ledStatestr);

    client.publish(led_state_topic, msg);
  }
}

unsigned long tHeartbeat = 0;

void taskHeartbeat() {
  if (millis() - tHeartbeat >= 5000) {
    tHeartbeat = millis();

    int uptime = millis() / 1000;
    int rssi = WiFi.RSSI();

    char msg[64];
    snprintf(msg, sizeof(msg), "{\"uptime\":%d,\"rssi\":%d}", uptime, rssi);

    client.publish(heartbeat_topic, msg);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void loop() {
  handleWiFi();
  handleMQTT();
  client.loop();
  handleIO();
  taskPublish();
  taskHeartbeat();
}
