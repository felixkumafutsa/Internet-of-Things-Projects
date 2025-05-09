
#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
int pos = 0;    // variable to store the servo position

int servoPin = 18;


void setup() {
  myservo.attach(servoPin);  // attaches the servo on pin 18 to the servo object
  Serial.begin(9600);
}

void loop() {

  for (pos = 20; pos <= 120; pos += 1) {  // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);  // tell servo to go to position in variable 'pos'
    delay(15);           // waits 15ms for the servo to reach the position
  }
  for (pos = 120; pos >= 20; pos -= 1) {  // goes from 180 degrees to 0 degrees
    myservo.write(pos);                  // tell servo to go to position in variable 'pos'
    delay(15);                           // waits 15ms for the servo to reach the position
  }
}
