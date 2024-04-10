#include <Arduino.h>

bool high_level = true;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  pinMode(12, OUTPUT);
  digitalWrite(12, high_level ? HIGH : LOW);
}

void loop() {
  digitalWrite(12, high_level ? HIGH : LOW);
  high_level = !high_level;

  MOSI;
}