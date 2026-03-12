#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "****";
const char* password = "*****";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* led_cmd_topic = "home/room1/esp32/led/cmd";
const char* led_state_topic = "home/room1/esp32/led/state";

const int ledPin = 19;
const int WIFIledPin = 18;
const int MQTTledPin = 21;

WiFiClient espClient;
PubSubClient client(espClient);

bool ledState = false;

void callback(char* topic, byte* payload, unsigned int length) {
  String message;

  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }

  if (String(topic) == led_cmd_topic) {
    if (message == "ON") {
      ledState = true;
    } else if (message == "OFF") {
      ledState = false;
    }
    client.publish(led_state_topic, ledState ? "ON" : "OFF", true);
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

void handleStatusLEDs() {
  static unsigned long lastBlink = 0;
  static bool blinkState = false;

  bool wifiConnected = (WiFi.status() == WL_CONNECTED);
  bool mqttConnected = client.connected();

  if (millis() - lastBlink > 150) {
    lastBlink = millis();
    blinkState = !blinkState;
  }

  if (!wifiConnected)
    digitalWrite(WIFIledPin, blinkState);
  else
    digitalWrite(WIFIledPin, LOW);

  if (wifiConnected && !mqttConnected)
    digitalWrite(MQTTledPin, blinkState);
  else
    digitalWrite(MQTTledPin, LOW);
}


enum SystemState {
  CONNECTING_WIFI,
  CONNECTING_MQTT,
  RUNNING
};

SystemState state = CONNECTING_WIFI;

void handleStateMachine() {
  switch (state) {

    case CONNECTING_WIFI:
      handleWiFi();

      if (WiFi.status() == WL_CONNECTED) {
        state = CONNECTING_MQTT;
      }
      break;

    case CONNECTING_MQTT:
      handleMQTT();

      if (client.connected()) {
        state = RUNNING;
      }

      if (WiFi.status() != WL_CONNECTED) {
        state = CONNECTING_WIFI;
      }
      break;

    case RUNNING:
      client.loop();
      handleIO();

      if (WiFi.status() != WL_CONNECTED) {
        state = CONNECTING_WIFI;
      } else if (!client.connected()) {
        state = CONNECTING_MQTT;
      }
      break;
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(WIFIledPin, OUTPUT);
  pinMode(MQTTledPin, OUTPUT);
  handleWiFi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  handleMQTT();
}

void loop() {
  handleStateMachine();
  handleStatusLEDs();
}