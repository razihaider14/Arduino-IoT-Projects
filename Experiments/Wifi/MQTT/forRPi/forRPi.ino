#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>

const char* ssid = "*****";
const char* password = "*****";

const char* ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDlzCCAn+gAwIBAgIUXnzg9Db5vUEkWLKHHBfu5tYiGMUwDQYJKoZIhvcNAQEL
BQAwWzELMAkGA1UEBhMCQVUxEzARBgNVBAgMClNvbWUtU3RhdGUxITAfBgNVBAoM
GEludGVybmV0IFdpZGdpdHMgUHR5IEx0ZDEUMBIGA1UEAwwLUlBJLU1RVFQtQ0Ew
HhcNMjYwMjIxMDkwODQ5WhcNMzYwMjE5MDkwODQ5WjBbMQswCQYDVQQGEwJBVTET
MBEGA1UECAwKU29tZS1TdGF0ZTEhMB8GA1UECgwYSW50ZXJuZXQgV2lkZ2l0cyBQ
dHkgTHRkMRQwEgYDVQQDDAtSUEktTVFUVC1DQTCCASIwDQYJKoZIhvcNAQEBBQAD
ggEPADCCAQoCggEBALUa1G/K6Bh+huJmGLOmOPYS5VqUZbZ9nB6CGSKKAhLmlMN7
fPsupTcEXNqDBYRqCuI9e6jLWmuwh4raoeN+mM73T2zZB9nXmgZ9C9u8nZ/MDCu8
30pSuRW8ZUP5mL04f902kt9pY0FMNMn43nQcv1HBmumFoyIbUM+YdDzQ9rdeJi3S
8upMgVrAD3H3gmk3bfoSraBlXIqmJykVB9OZ13Q5Anq2FUWe7IYQQsKI4jYGzg/H
ubV4gVLqE4Myo8OSjDZujMjID4CQXn0Nj2T01eN+01pJOmS9zea1Rs4W4eCKSCQ3
0GdaqBcPSj4/ABjYLJ52bIqHmO5hW+3bNTFa2ZcCAwEAAaNTMFEwHQYDVR0OBBYE
FCpyMNTnYRR5lg9laVAYjjwTb+fgMB8GA1UdIwQYMBaAFCpyMNTnYRR5lg9laVAY
jjwTb+fgMA8GA1UdEwEB/wQFMAMBAf8wDQYJKoZIhvcNAQELBQADggEBAI8Z98Fg
7kC2KPqE06xV2vbTW1JGIFEP9R3KZFETznXw1UkASSw/nUC9nWSItXjPP8CL9kRr
Vq/tvaGFNkNzMZ1b0iu8MB1T4/8BugtIxfcqPUZM3A9zV900yjlcqZbO1oP5s1WU
ZxFpKKaSM8ds2I1W+hGmjuOlum8AOVjwpBUiwXemtxAwDTPBaVmTFbCxyfQdpy60
RF3yMsggzICdcpE05xtsNJ+dB9WB7ygNV3BYlD8UVnZMRyzLhPcm63Mr8TXS6KgG
0V49u1DBVx/oZq4eaiSPnKGNy/PSGPMyU+ABJwDyQn33nNe9fxQWXl/csAsyjKu3
uQFgXMg/cVMeERo=
-----END CERTIFICATE-----
)EOF";

const char* mqtt_server = "ip";
const int mqtt_port = 8883;

const char* led_cmd_topic = "home/esp32/cmd";
const char* led_state_topic = "home/esp32/state";
const char* sensor_topic = "home/esp32/sensor";
const char* status_topic = "home/esp32/status";
const char* heartbeat_topic = "home/esp32/heartbeat";

const int ledPin = 19;

WiFiClientSecure espClient;
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
      Serial.print("MQTT failed, rc=");
      Serial.println(client.state());

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

  espClient.setCACert(ca_cert);
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