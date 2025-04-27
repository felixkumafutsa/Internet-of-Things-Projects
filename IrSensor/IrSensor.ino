#include <IRremote.hpp>
#define button1 0xF30CFF00
#define button2 0xE718FF00
#define ledPin 2
#define irReceiver 4
#define buzzer 3




void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  IrReceiver.begin(irReceiver, ENABLE_LED_FEEDBACK); 
}

void loop() {
  if (IrReceiver.decode()) {
   uint32_t rawData= IrReceiver.decodedIRData.decodedRawData;
   if(rawData == button1) {
    delay(2 000);
    digitalWrite(ledPin, HIGH);
    analogWrite(buzzer, 255);
    
    
    }
    if(rawData == button2) {
      digitalWrite(ledPin, LOW);
      analogWrite(buzzer, 0);
      }
      IrReceiver.resume(); 
  }

}
