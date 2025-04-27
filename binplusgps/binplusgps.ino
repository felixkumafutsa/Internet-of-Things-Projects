#include <Arduino.h>
#include <HC_SR04.h>
#include <Servo.h>
#include "TinyGPS++.h"
#include "SoftwareSerial.h"

Servo myservo;                           // create servo object to control a servo
int pos = 0;                             // variable to store the servo position
HC_SR04<7> sensor(8);                    // sensor with echo and trigger pin
HC_SR04<9> sensor1(13);                  // sensor with echo and trigger pin
SoftwareSerial serial_connection(19, 21);  //tx,rx
TinyGPSPlus gps;                         // GPS object to process the NMEA data
void setup() {
  Serial.begin(9600);             //This opens up communications to the Serial monitor in the Arduino IDE
  serial_connection.begin(9600);  //This opens up communications to the GPS
  sensor.begin();
  sensor1.begin();
  myservo.attach(11);           // attaches the servo on pin 9 to the servo object
  Serial.println("GPS Start");  //To show in the serial monitor that the sketch has started
}

void loop() {
  sensor.startMeasure();
  sensor1.startMeasure();
  while (serial_connection.available())  //While there are incoming characters  from the GPS
  {
    gps.encode(serial_connection.read());  //This feeds the serial NMEA data into the library one char at a time
  }
  if (gps.location.isUpdated())  //This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
  {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.print("Satellite Count:");
    Serial.println(gps.satellites.value());
    Serial.print("Latitude:");
    Serial.println(gps.location.lat(), 6);
    Serial.print("Longitude:");
    Serial.println(gps.location.lng(), 6);

    Serial.print("Altitude Feet:");
    Serial.println(gps.altitude.feet());
    Serial.println("");

    Serial.print("Date: ");
    if (gps.date.isValid()) {
      Serial.print(gps.date.month());
      Serial.print("/");
      Serial.print(gps.date.day());
      Serial.print("/");
      Serial.println(gps.date.year());
    }

    Serial.print("Time: ");
    if (gps.time.isValid()) {
      if (gps.time.hour() < 10) Serial.print(F("0"));
      Serial.print(gps.time.hour());
      Serial.print(":");
      if (gps.time.minute() < 10) Serial.print(F("0"));
      Serial.print(gps.time.minute());
      Serial.print(":");
      if (gps.time.second() < 10) Serial.print(F("0"));
      Serial.print(gps.time.second());
      Serial.print(".GMT");
    }
    Serial.println("");
    delay(2000);
  }
  if (sensor.getDist_cm() > 20) {
    Serial.print("WasteLevel  ");
    Serial.print(sensor.getDist_cm());
    Serial.println("  Waste Level is LOW");
  } else if (sensor.getDist_cm() < 20 && sensor.getDist_cm() > 13) {
    Serial.print("WasteLevel  ");
    Serial.println(sensor.getDist_cm());
  } else if (sensor.getDist_cm() < 13) {
    Serial.print("WasteLevel  ");
    Serial.println(sensor.getDist_cm());
  }
  if (sensor1.getDist_cm() > 50) {
    openRid();
  } else {
    closeRid();
  }
  delay(1000);
}


void openRid() {
  for (pos = 180; pos >= 90; pos -= 1) {  // goes from 180 degrees to 0 degrees
    myservo.write(pos);                   // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15 ms for the servo to reach the position
  }
}


void closeRid() {
  for (pos = 90; pos <= 180; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
                         // delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
