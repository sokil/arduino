#include <Arduino.h>


int latchPin = 8;
int clockPin = 12;
int dataPin = 11;

bool sent = false;

void setup() {
    Serial.begin(9600);

    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
}

void loop() {
    int i;
    for (i = 0; i <= 255; i++) {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, MSBFIRST, i);
        digitalWrite(latchPin, HIGH);
        Serial.println(i);
        delay(1000);
    }
}