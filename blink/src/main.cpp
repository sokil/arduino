#include <Arduino.h>

#ifndef LED_PIN
#define LED_PIN 8
#endif

#ifdef RGB_LED_PIN
#include <Adafruit_NeoPixel.h>
#endif

#define NUMPIXELS 1

Adafruit_NeoPixel pixels(NUMPIXELS, RGB_LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(LED_PIN, OUTPUT);

  #ifdef RGB_LED_PIN
  pixels.begin();
  #endif
}

void loop() {
  for (int i = 1; i < 5; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }

  #ifdef RGB_LED_PIN
  pixels.clear();

  for(int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150, 0, 0));
    pixels.show();
    delay(500);
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));
    pixels.show();
    delay(500);
    pixels.setPixelColor(i, pixels.Color(0, 0, 150));
    pixels.show();
    delay(500);
  }
  #endif
}