// Code for blinking a laser module using Arduino
// Author: Oyvind N. Dahl
// Website: https://www.build-electronic-circuits.com/

void setup() {
  pinMode(4, OUTPUT);  
}

void loop() {
  digitalWrite(4, HIGH);
  delay(300);
  
  digitalWrite(4, LOW);
  delay(700);
}
