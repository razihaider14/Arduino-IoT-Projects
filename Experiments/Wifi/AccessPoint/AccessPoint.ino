#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "ESP32_AP";
const char* pass = "esp32wifi123";

IPAddress local_ip(192,168,1,1);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

#define ledPin 18

WebServer server(80);

bool ledStatus = LOW;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  WiFi.softAPConfig(local_ip,gateway,subnet);
  WiFi.softAP(ssid,pass);
  delay(1000);

  Serial.print("AP SSID: ");
  Serial.println(WiFi.softAPSSID());

  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());


  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledON);
  server.on("/ledoff", handle_ledOFF);
  server.onNotFound(handle_NotFound);
  server.begin();
  Serial.println("HTTP Server Started");

}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}

String getHTML() {
  String htmlcode = "<!DOCTYPE html> <html>\n";
  htmlcode += "<head><meta name =\"viewport\" content = \"width = device-width, initial-scale = 1.0, user-scalable = no\">\n";
  htmlcode += "<title>LED Control</title>\n";
  htmlcode += "</head>\n";
  htmlcode += "<body>\n";
  htmlcode += "<h1>ESP32 Web Server</h1>\n";
  htmlcode += "<h3>Access Point Mode</h3>\n";
  if(ledStatus){
    htmlcode += "<p>LED Status: ON</p><a href=\"/ledoff\">Turn it OFF</a>\n";
  }
  else{
    htmlcode += "<p>LED Status: OFF</p><a href=\"/ledon\">Turn it ON</a>\n";
  }
  htmlcode += "</body>\n</html>";

  return htmlcode;
}

void handle_OnConnect() {
  server.send(200, "text/html", getHTML());
}

void handle_ledON() {
  digitalWrite(ledPin, HIGH);
  ledStatus = HIGH;
  Serial.println("LED Status: ON");
  server.send(200, "text/html", getHTML());
}

void handle_ledOFF() {
  digitalWrite(ledPin, LOW);
  ledStatus = LOW;
  Serial.println("LED Status: OFF");
  server.send(200, "text/html", getHTML());
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not Found");
}