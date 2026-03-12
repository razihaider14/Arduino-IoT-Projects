#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>

const char* ssid = "******";
const char* password = "******";

const char* mqtt_server = "ip";
const int mqtt_port = 1883;

const char* led_cmd_topic = "home/room1/esp32/led/cmd";
const char* led_state_topic = "home/room1/esp32/led/state";
const char* sensor_topic = "home/room1/esp32/sensor";
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

      if (client.connect("ESP32_Client_01", "esp32", "123456",status_topic , 0 , true , "OFFLINE")) {
        client.subscribe(led_cmd_topic);
        client.publish(status_topic, "ONLINE", true);
      } 
    }
  }
}

void handleIO() {
  digitalWrite(ledPin, ledState);
}

void stateChange() {
  const char* s = ledState ? "ON" : "OFF";
  char msg[32];
  snprintf(msg, sizeof(msg), "{\"led\":\"%s\"}", s);
  client.publish(led_state_topic, msg, true); 
}

unsigned long tSensor = 0;
void taskSensor() {
  if (millis() - tSensor >= 1000) {  
    tSensor = millis();

    float temp = random(200, 350) / 10.0;  
    int hum = random(40, 80);  

    char msg[64];
    snprintf(msg, sizeof(msg), "{\"temp\":%.1f,\"hum\":%d}", temp, hum);

    client.publish(sensor_topic, msg);
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
  randomSeed(micros());
  pinMode(ledPin, OUTPUT);

  WiFi.begin(ssid, password);

  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  ArduinoOTA.setHostname("esp32-room1");
  ArduinoOTA.setPassword("1234");
  ArduinoOTA.begin();
}


void loop() {
  ArduinoOTA.handle();
  handleWiFi();
  handleMQTT();
  client.loop();
  handleIO();
  taskSensor();
  taskHeartbeat();
}

