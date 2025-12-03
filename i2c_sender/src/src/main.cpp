#include <Wire.h>
#include <Arduino.h>

#define PIN_I2C_SDA 5
#define PIN_I2C_SCL 6
#define PIN_LED 8

const uint8_t DEV_ADDR_7BIT = 0x70; // 0xE0 >> 1

void setup()
{
  Serial.begin(9600);
  Serial.println("\nI2C Scanner");
  Wire.begin(PIN_I2C_SDA, PIN_I2C_SCL, 100000);

  pinMode(PIN_LED, OUTPUT);
}


void loop()
{
  uint8_t data[5] = {1, 2, 3, 4, 5};

  digitalWrite(PIN_LED, HIGH);
  Wire.beginTransmission(DEV_ADDR_7BIT);
  Wire.write(data, 5);
  Wire.endTransmission();
  delay(100);
  digitalWrite(PIN_LED, LOW);

  delay(1000);
}