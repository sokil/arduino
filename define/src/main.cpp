#include <Arduino.h>

#define VERSION 1
#define VERSION 2

void setup()
{
  USBSerial.begin(115200);
}

void loop()
{
  printf("VERSION: %d", VERSION);
  delay(1000);
}