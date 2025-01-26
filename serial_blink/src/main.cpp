#include <Arduino.h>

#define RX_PIN 9 // tbs crossfire
#define TX_PIN 10 // tbs crossfire

void setup() {
  Serial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  Serial.println("Initialized");
}

void loop() {
  Serial.println("ping");
  delay(500);
}
