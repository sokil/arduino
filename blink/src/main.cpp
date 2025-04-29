#include <Arduino.h>

#ifndef LED_PIN
#define LED_PIN 8
#endif

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  for (int i = 1; i < 20; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(i * 100);
    digitalWrite(LED_PIN, LOW);
    delay(i * 100);
  }

}