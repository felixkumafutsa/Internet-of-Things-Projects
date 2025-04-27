int redPin= 5;
int greenPin = 4;
int bluePin = 3;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  setColor(255, 0, 255); // Red Color
  delay(2000);
  setColor(0, 255, 0); // Green Color
  delay(2000);
  setColor(0, 0, 255); // Blue Color
  delay(2000);
  setColor(255, 255, 255); // White Color
  delay(2000);
  
  setColor(255, 255, 192); // White Color
  delay(2000);
  setColor(170, 0, 255); // Purple Color
  delay(100);
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}