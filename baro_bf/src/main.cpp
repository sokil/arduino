#include <Arduino.h>
#include <Wire.h>

// On an arduino UNO: A4(SDA), A5(SCL)

// BME280 default I2C address is 0x76 (0x77 if SDO pin is high)
#define I2C_ADDRESS 0x76

// BME280 Registers
#define REG_CHIP_ID 0xD0
#define REG_CONTROL_HUM 0xF2
#define REG_CONTROL 0xF4
#define REG_CONFIG 0xF5
#define REG_PRESSURE 0xF7
#define REG_TEMP 0xFA
#define REG_HUM 0xFD

uint8_t prevRegisters[256];

bool initBaro()
{
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(REG_CONTROL_HUM); // Humidity control
  Wire.write(0x01);            // Set oversampling for humidity (x1)
  Wire.endTransmission();

  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(REG_CONTROL); // Control register
  Wire.write(0x27);        // Set normal mode, oversampling for temperature and pressure (x1)
  Wire.endTransmission();

  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(REG_CONFIG); // Config register
  Wire.write(0xA0);       // Standby time 1000ms, filter off
  Wire.endTransmission();

  return true;
}

uint8_t read8(uint8_t reg)
{
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(I2C_ADDRESS, (uint8_t)1);
  uint8_t value = Wire.read();
  return value;
}

// Helper function to read 16-bit value (big-endian) from a register
uint16_t read16(uint8_t reg)
{
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(I2C_ADDRESS, (uint8_t)2);
  uint16_t value = (Wire.read() << 8) | Wire.read();
  return value;
}

// Helper function to read 24-bit value from a register
uint32_t read24(uint8_t reg)
{
  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(reg);
  Wire.endTransmission();

  Wire.requestFrom(I2C_ADDRESS, (uint8_t)3);
  uint32_t value = (Wire.read() << 16) | (Wire.read() << 8) | Wire.read();
  return value;
}

float readChipId()
{
  int16_t temp_raw = read16(REG_CHIP_ID) >> 4;

  return temp_raw;
}

// Read temperature from BME280
float readTemperature()
{
  int32_t temp_raw = read24(REG_TEMP) >> 4;

  // Apply calibration (simple calculation for demonstration purposes)
  return temp_raw / 100.0; // Adjust this for proper scaling and offset based on calibration values
}

// Read pressure from BME280
float readPressure()
{
  int32_t press_raw = read24(REG_PRESSURE) >> 4;

  // Apply calibration (simple calculation for demonstration purposes)
  return press_raw / 100.0; // Adjust this for proper scaling and offset based on calibration values
}

// Read humidity from BME280
float readHumidity()
{
  uint16_t hum_raw = read16(REG_HUM);

  // Apply calibration (simple calculation for demonstration purposes)
  return hum_raw / 1024.0; // Adjust this for proper scaling and offset based on calibration values
}

void setup()
{
  Wire.begin();
  Serial.begin(9600);

  if (!initBaro())
  {
    Serial.println("Baro initialization failed!");
    while (1)
      ; // halt
  }

  Serial.println("Baro Initialized");
}

void printDiffRegisters()
{
  Serial.println("Diff registers:");

  int i;
  int value;
  char hexBuffer[5];
  for (i = 0; i <= 255; i++) {
    value = read8((uint8_t) i);

    if (value != prevRegisters[i]) {
        Serial.print("Register: ");
        sprintf(hexBuffer, "0x%x", i);
        Serial.print(hexBuffer);
        Serial.print(", Value: ");
        Serial.println(value);
    }

    prevRegisters[i] = value;
  }
}

void printAllRegisters()
{
  Serial.println("All non-zero registers:");

  int i;
  for (i = 0; i <= 255; i++) {
    Wire.beginTransmission(I2C_ADDRESS);
    Wire.write(i);
    Wire.endTransmission();

    Wire.requestFrom(I2C_ADDRESS, (uint8_t)2);
    int value = Wire.read();

    if (value > 0) {
        Serial.print("Register: ");
        char hexBuffer[5];
        sprintf(hexBuffer, "0x%x", i);
        Serial.print(hexBuffer);
        Serial.print(", Value: ");
        Serial.println(value);
    }
  }
}

void printValues()
{
  Serial.println("Parsed values:");

  float chipId = readChipId();
  float temperature = readTemperature();
  float pressure = readPressure();
  float humidity = readHumidity();

  Serial.print("ChipId: ");
  Serial.println(chipId);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Pressure: ");
  Serial.print(pressure / 100.0); // Convert to hPa
  Serial.println(" hPa");

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}

void loop()
{
  printDiffRegisters();
  // printAllRegisters();
  // printValues();

  delay(1000);
}