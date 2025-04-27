
#include <Arduino.h>
#include <HC_SR04.h>

HC_SR04<2> sensor(8);   // sensor with echo and trigger pin

void setup() {  Serial.begin(9600);  sensor.begin(); }

void loop() {
  sensor.startMeasure();
  Serial.println(sensor.getDist_cm());
  delay(1000);
}
                      
