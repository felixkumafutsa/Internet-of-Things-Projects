#include <Arduino.h>
#include <HC_SR04.h>

HC_SR04<14> sensor(12);  // sensor with echo and trigger pin, D6(trig),D5(echo)
HC_SR04<13> sensor1(15);

void setup() {
  Serial.begin(9600);
  sensor.begin();
  sensor1.begin();
}

void loop() {
  sensor.startMeasure();
  sensor1.startMeasure();
  Serial.print("sensor_value");
  Serial.println(sensor.getDist_cm());
  Serial.print("sensor_1value");
  Serial.println(sensor1.getDist_cm());
  delay(1000);
}
