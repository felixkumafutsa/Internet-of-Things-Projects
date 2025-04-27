int ir=13;

void setup() {
  pinMode(ir,INPUT);
  Serial.begin(9600);
}

void loop() {
  int irvalue=digitalRead(ir);
  if (irvalue==LOW) {
    Serial.println("Low");
  } else {
    Serial.println("High");
  }
  delay(100);
}
