#include <Arduino.h>

#ifndef INPUT_PIN
#define INPUT_PIN 3
#endif

#ifndef LID_PIN
#define LED_PIN 8
#endif

void setup() {
  pinMode(INPUT_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  int level = digitalRead(INPUT_PIN);
  digitalWrite(LED_PIN, level ? LOW : HIGH);
  delay(10);
}