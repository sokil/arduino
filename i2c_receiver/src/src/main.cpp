#include <Arduino.h>
#include <Wire.h>

#define PIN_I2C_SDA 5
#define PIN_I2C_SCL 6
#define PIN_LED 8

const uint8_t SLAVE_ADDR = 0x70;

uint8_t buf[5];
volatile uint8_t count = 0;

void receiveEvent(int howMany)
{
  count = 0;
  while (Wire.available() && count < sizeof(buf))
  {
    buf[count++] = Wire.read();
  }
}

void setup()
{
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(9600);
  Serial.println("I2C Slave ready");

  // ESP32-style begin: SDA, SCL, address
  Wire.begin(SLAVE_ADDR, PIN_I2C_SDA, PIN_I2C_SCL, 100000);

  Wire.onReceive(receiveEvent);
}

void loop()
{
  if (count > 0)
  {
    digitalWrite(PIN_LED, HIGH);

    Serial.print("Received ");
    Serial.print(count);
    Serial.print(" bytes: ");

    for (int i = 0; i < count; i++)
    {
      Serial.print(buf[i]);
      Serial.print(" ");
    }
    Serial.println();

    count = 0;

    delay(50);
    digitalWrite(PIN_LED, LOW);
  }
}