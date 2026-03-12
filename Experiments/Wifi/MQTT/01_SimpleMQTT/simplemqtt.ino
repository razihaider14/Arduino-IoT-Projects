#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "*****";
const char* password = "*****";

const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;

const char* led_cmd_topic   = "home/room1/esp32/led/cmd";
const char* led_state_topic = "home/room1/esp32/led/state";

const int ledPin = 18;

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

    digitalWrite(ledPin, ledState ? HIGH : LOW);

    client.publish(led_state_topic, ledState ? "ON" : "OFF", true);
  }
}

void setup_wifi() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32_Client_01")) {
      client.subscribe(led_cmd_topic);
    } else {
      delay(2000);
    }
  }
}

void setup() {
  pinMode(ledPin, OUTPUT);
  setup_wifi();

  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}
