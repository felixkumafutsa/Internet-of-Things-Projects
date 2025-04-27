// include all libraries
#include <Arduino.h>
#include <HC_SR04.h>
#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>


#define DHTPIN 4  // what digital pin we're connected to
// Uncomment whatever type you're using!
#define DHTTYPE DHT11  // DHT 11
DHT dht(DHTPIN, DHTTYPE);

HC_SR04<14> sensor(12);  // sensor with echo and trigger pin, D6(trig),D5(echo)
HC_SR04<13> sensor1(15);

float tValue;  //
float hValue;
float feedSensor;
float waterSensor;
const int refresh = 3;  //3 seconds
// ****** DHT settings end

#ifndef STASSID
#define STASSID "CodeReaper"   // Your WiFi SSID
#define STAPSK "kalakalakala"  //Your WiFi password
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);


void sendTemp() {

  String page = "<!DOCTYPE html>\n\n";
  page += "    <meta http-equiv='refresh' content='";
  page += String(refresh);  // how often temperature is read
  page += "'/>\n";
  page += "<html>\n";
  page += "<body>\n";
  page += "<h1>ESP8266 DHT11 WEB SERVER</h1>\n";
  page += "<h3>GIRLS CAN CODE BOOTCAMP</h3>\n";

  page += "<p style=\"font-size:30px;\">Temperature";
  page += "<p style=\"color:red; font-size:50px;\">";
  page += String(tValue, 2);
  page += "</p>\n";

  page += "<p style=\"font-size:30px;\">Humidity";
  page += "<p style=\"color:red; font-size:50px;\">";
  page += String(hValue, 2);
  page += "</p>\n";

  page += "<p style=\"font-size:30px;\">feed level";
  page += "<p style=\"color:red; font-size:50px;\">";
  page += String(feedSensor, 2);
  page += "</p>\n";

  page += "<p style=\"font-size:30px;\">water level";
  page += "<p style=\"color:red; font-size:50px;\">";
  page += String(waterSensor, 2);
  page += "</p>\n";

  page += "</body>\n";
  page += "</html>\n";
  server.send(200, "text/html", page);
}

void handleNotFound() {

  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void) {
  dht.begin();
  sensor.begin();
  sensor1.begin();
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  if (WiFi.status() == WL_CONNECTED) {
    uint8_t macAddr[6];
    WiFi.macAddress(macAddr);
    Serial.printf("Connected, mac address: %02x:%02x:%02x:%02x:%02x:%02x\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("robojaxDHT")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", sendTemp);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
  float c = dht.readTemperature();      // Read temperature as Celsius (the default)
  float h = dht.readHumidity();         // Reading humidity
  float f = dht.readTemperature(true);  // Read temperature as Fahrenheit (isFahrenheit = true)

  Serial.println(c);
  sensor.startMeasure();
  sensor1.startMeasure();
  feedSensor = sensor.getDist_cm();
  waterSensor = sensor1.getDist_cm();
  tValue = c;
  hValue = h;
  delay(300);
}