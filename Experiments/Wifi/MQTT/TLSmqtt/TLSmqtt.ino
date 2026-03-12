#include <ArduinoJson.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include <ArduinoOTA.h>

const char* ssid = "******";
const char* password = "******";

const char* ca_cert = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDazCCAlOgAwIBAgIUFPMiIGVg9Ory3DDvkSjruG14dHkwDQYJKoZIhvcNAQEL
BQAwRTELMAkGA1UEBhMCQVUxEzARBgNVBAgMClNvbWUtU3RhdGUxITAfBgNVBAoM
GEludGVybmV0IFdpZGdpdHMgUHR5IEx0ZDAeFw0yNjAyMDkwNTM1NTBaFw0zNjAy
MDcwNTM1NTBaMEUxCzAJBgNVBAYTAkFVMRMwEQYDVQQIDApTb21lLVN0YXRlMSEw
HwYDVQQKDBhJbnRlcm5ldCBXaWRnaXRzIFB0eSBMdGQwggEiMA0GCSqGSIb3DQEB
AQUAA4IBDwAwggEKAoIBAQCdD/hemq+GdHu94UWq/aZUekVS09YiF0TOlBjzgUG6
JKNNA77+K7UIGFx+8zKULRjpM0pi153zsTMKNHIxlqJFLmKQtBARx2dXco/FbhT3
72RT8kh9O3SMRNTVsJj8WiE9HkUWj0YjsLXXTXNHYd5Q/xcW/LLHgM3GlLoDrtMq
j3sDas2LPv/fT4y9HZBpIDGmE4fU580XdHuQT4SxxqzagjcACpnQ3vzp+Jy6X2ua
X5fbEryt4FOZmHYmSdb7o2DexIhHdGTWOCUB7rBRL5Pfybjjt4vFKwmQxnGUgCF5
fJo/YEcN7oW92QI02gaayi3m0v4DzJmkR51HbQS5PebxAgMBAAGjUzBRMB0GA1Ud
DgQWBBQ28tHNskjt78uddiyh1nNaD2CSJDAfBgNVHSMEGDAWgBQ28tHNskjt78ud
diyh1nNaD2CSJDAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQBi
EwkXq/R0mgLPFxdpumus3xg3KApZ5z07V16wvqUOtFcbQdoOvnpEvHN01RaMXdJr
uD4yPsb0e12cBs1LXihrAXf4kpR85mj9aPKZTH3WvGcL9aj7hkCqrViIvT5IyTAn
A6FT4zPCz7xcmyquiLDMtJeuYbr54m2nREqtcpCBqmQLIAJ/Vz+zI/3KQGuJQnyV
8J+kyolL9uNHam3vt77rl83LLHdvXbPrzT5ua28Q7AMGqgkv3bVdzB4RWadkCerL
vM/uZaJ4rXK2Rd0ssQ9jmEMFUi1vYi2gnyzujo+U61FvV/jjUn7hrms5pYjQTrOG
XIM+qdKuF9Hxc7+HvbWK
-----END CERTIFICATE-----
)EOF";

const char* mqtt_server = "ip";
const int mqtt_port = 8883;

const char* led_cmd_topic = "home/room1/esp32/led/cmd";
const char* led_state_topic = "home/room1/esp32/led/state";
const char* sensor_topic = "home/room1/esp32/sensor";
const char* status_topic = "home/room1/esp32/status";
const char* heartbeat_topic = "home/room1/esp32/heartbeat";

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

