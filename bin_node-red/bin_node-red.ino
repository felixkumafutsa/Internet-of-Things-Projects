#include <Arduino.h>
#include <VARSTEP_ultrasonic.h>
#include <Servo.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>


#define trigger_pin 8
#define echo_pin 2
#define trigger_pin1 10
#define echo_pin1 5
static const int RXPin = 4, TXPin = 3;
static const uint32_t GPSBaud = 4800;

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

double distance_cm;
double distance_cm_from_bin;
VARSTEP_ultrasonic first_HCSR04(trigger_pin, echo_pin); // You can create multiple instances for multiple sensors
VARSTEP_ultrasonic second_HCSR04(trigger_pin1, echo_pin1); // You can create multiple instances for multiple sensors

void setup() {
    myservo.attach(9);  // attaches the servo on pin 9 to the servo object
    Serial.begin(9600);
     ss.begin(GPSBaud);
    }

void loop() {
  distance_cm = first_HCSR04.distance_cm();
  distance_cm_from_bin = second_HCSR04.distance_cm();
    Serial.print(distance_cm_from_bin);
//  if(distance_cm>20){
//    Serial.print(distance_cm);
//  }
//  else if(distance_cm<20 && distance_cm>13){
//    Serial.print(distance_cm);
//  }
//    else if(distance_cm<13){
//    Serial.print(distance_cm);
//  }
  if(distance_cm_from_bin>50){
    openRid();
  }
  else{
    closeRid();
  }
  delay(1000);
}

void openRid(){

   for (pos = 180; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    //delay(15);                       // waits 15 ms for the servo to reach the position
  }
}


void closeRid(){
 for (pos = 90; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
   // delay(15);                       // waits 15 ms for the servo to reach the position
  }
}
