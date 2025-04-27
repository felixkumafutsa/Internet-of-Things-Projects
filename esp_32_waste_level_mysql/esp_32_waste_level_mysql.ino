#include <Wire.h>
#include <ESP32Servo.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <UrlEncode.h>
#include <TinyGPS++.h>



#define echoPin1 2
#define trigPin1 4
#define echoPin 12
#define trigPin 14
#define GPS_TX_PIN 19
#define GPS_RX_PIN 21

String URL = "http://192.168.43.188/waste_level_project/test_data.php";

const char* ssid = "TechNexus";
const char* password = "techies@097";
String phoneNumber = "+265884743068";
String apiKey = "3688662";

Servo myservo;
TinyGPSPlus gps;
unsigned long timestamp;
float lat = 0;
float lng = 0;

int pos = 180;
int ir = 25;
int servoPin = 18;
int sensor_data = 0;
long duration, distance, distance1;

void setup() {
  Serial.begin(115200, SERIAL_8N1, GPS_TX_PIN, GPS_RX_PIN);
  connectWiFi();
  myservo.attach(servoPin);
  pinMode(ir, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
}
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    connectWiFi();
  }



  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration = pulseIn(echoPin1, HIGH);
  distance1 = duration / 58.2;


  if (distance1 <= 20) {
    myservo.write(0);
    delay(15);
  } else {
    myservo.write(120);
    delay(15);
  }

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
  sensor_data = 23 - distance;

  String postData = "sensor_data=" + String(sensor_data);

  HTTPClient http;
  http.begin(URL);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  int httpCode = http.POST(postData);
  String payload = http.getString();

  if (sensor_data > 5) {
    // Send Message to WhatsAPP
    sendMessage("Bin A located at: is full");
  }

  get_gps_data();
  Serial.print("URL : ");
  Serial.println(URL);
  Serial.print("Data: ");
  Serial.println(postData);
  Serial.print("httpCode: ");
  Serial.println(httpCode);
  Serial.print("payload : ");
  Serial.println(payload);
  Serial.println("--------------------------------------------------");
  delay(1000);
}


void connectWiFi() {
  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print("connected to : ");
  Serial.println(ssid);
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());
}

void sendMessage(String message) {

  // Data to send with HTTP POST
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + phoneNumber + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  HTTPClient http;
  http.begin(url);

  // Specify content-type header
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");

  // Send HTTP POST request
  int httpResponseCode = http.POST(url);
  if (httpResponseCode == 200) {
    Serial.print("Message sent successfully");
  } else {
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }

  // Free resources
  http.end();
}

// Function to get GPS data
void get_gps_data() {
  Serial.println("Getting GPS data: ");
  while (Serial1.available() > 0) {
    gps.encode(Serial1.read());
  }
  // Check if GPS location is valid
  if (gps.location.isValid()) {
    lat = gps.location.lat();
    lng = gps.location.lng();
    Serial.print("Latitude = ");
    Serial.println(lat, 6);
    Serial.print("Longitude = ");
    Serial.println(lng, 6);
  } else {
    Serial.println(F("Invalid GPS data"));
  }
  Serial.println();
}