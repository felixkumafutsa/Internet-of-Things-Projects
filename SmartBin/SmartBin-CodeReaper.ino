#include <Arduino.h>
#include <HC_SR04.h>
#include <Servo.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position
HC_SR04<3> sensor(4);   // sensor with echo and trigger pin
HC_SR04<9> sensor1(13);   // sensor with echo and trigger pin
SoftwareSerial serial_connection(5,6); //tx,rx 
TinyGPSPlus gps;// GPS object to process the NMEA data

void setup() {
    myservo.attach(11);  // attaches the servo on pin 9 to the servo object
    Serial.begin(9600);
    sensor.begin();
    sensor1.begin();
    Serial.println("DEEP LEARNING-ENHANCED WASTE MANAGEMENT SYSTEM");
 
    }

void loop() {

  sensor.startMeasure();
  sensor1.startMeasure();
  if(sensor.getDist_cm()>20){

    Serial.print("Waste distance from lid: : ");
    Serial.print(sensor.getDist_cm());
    Serial.println(", Waste Level is LOW");
  }
  else if(sensor.getDist_cm()<20 && sensor.getDist_cm()>13){
 
    Serial.print("Waste Level ");
    Serial.print(sensor.getDist_cm());
  }
    else if(sensor.getDist_cm()<13){

    Serial.print("Waste Level ");
    Serial.print(sensor.getDist_cm());
  }
  if(sensor1.getDist_cm()>50){
    openRid();
  }
  else{
    closeRid();
  }

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

  
