#include "Arduino.h"

// Power supply 5v
// Sound detector HW-484

const int analogInPin = 4;
const int digitalInPin = 5;
const int controlOutPin = 6;

bool controlEnabled = false;
int previousValue = LOW;

unsigned long lastChangeTime;

void setup() {
  pinMode(digitalInPin, INPUT);
  pinMode(controlOutPin, OUTPUT);
  Serial.begin(9200);

  lastChangeTime = millis();
}

void loop() {
    //Serial.println(analogRead(analogInPin));

    if (millis() - lastChangeTime > 100) {
        int currentValue = digitalRead(digitalInPin);

        if (previousValue != currentValue) {
            if (currentValue == HIGH) {
                lastChangeTime = millis();

                controlEnabled = !controlEnabled;

                digitalWrite(controlOutPin, controlEnabled);

                Serial.println("HIGH\n");
            } else {
                Serial.println("LOW\n");
            }

            previousValue = currentValue;
        }
    }

}