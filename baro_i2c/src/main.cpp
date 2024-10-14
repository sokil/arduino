#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_DPS310.h>
#include "Adafruit_BMP3XX.h"

// On an arduino UNO: A4(SDA), A5(SCL)

enum BAROMETER {
  UNDEFINED,
  BME280, // 0x76
  BMP085, // 0x77
  BMP180, // 0x77, NOT SUPPORTED
  MS5611, // 0x77, not supported
  QMP6988, // 0X70, not supported
  DPS310, // 0x77
  SPL06, // 0x76 or 0x77, clone of BMP280, not supported
  BMP3XX, // 0x77
};

#define ADDRESS 0x76

Adafruit_BME280 bme;
Adafruit_BMP085 bmp;
Adafruit_DPS310 dps;
Adafruit_BMP3XX bmp3xx;

Adafruit_Sensor *dps_temp = dps.getTemperatureSensor();
Adafruit_Sensor *dps_pressure = dps.getPressureSensor();

#define SEALEVELPRESSURE_HPA (1013.25)

enum BAROMETER detectedBarometer = UNDEFINED;

BAROMETER detectBarometer()
{
  if (bme.begin(ADDRESS)) {
    detectedBarometer = BME280;
    Serial.println("BME280 sensor initialized");
    return detectedBarometer; 
  }

  if (bmp.begin(ADDRESS)) {
    detectedBarometer = BMP085;
    Serial.println("BMP085 sensor initialized");
    return detectedBarometer;
  }

  if (dps.begin_I2C()) {
    // Setup highest precision
    dps.configurePressure(DPS310_64HZ, DPS310_64SAMPLES);
    dps.configureTemperature(DPS310_64HZ, DPS310_64SAMPLES);

    dps_temp->printSensorDetails();
    dps_pressure->printSensorDetails();

    detectedBarometer = DPS310;
    Serial.println("DPS310 sensor initialized");
    return detectedBarometer;
  }

  if (bmp3xx.begin_I2C()) {
    // Set up oversampling and filter initialization
    bmp3xx.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp3xx.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp3xx.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp3xx.setOutputDataRate(BMP3_ODR_50_HZ);

    detectedBarometer = DPS310;
    Serial.println("BMP3XX sensor initialized");
    return detectedBarometer;
  }

  Serial.println("No berometers found");
  while(1);
}

void printBME()
{
  // Read temperature, humidity, and pressure
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F; // hPa
  float altitude = bme.readAltitude(1013.25);  // Adjust for your local sea level pressure (hPa)

  // Print the values to the Serial Monitor
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");
}

void printBMP()
{
  // Read temperature, humidity, and pressure
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F; // hPa
  float altitude = bmp.readAltitude(1013.25);  // Adjust for your local sea level pressure (hPa)

  // Print the values to the Serial Monitor
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(altitude);
  Serial.println(" m");
}

void printPPS310()
{
  sensors_event_t temp_event, pressure_event;
  
  if (dps.temperatureAvailable()) {
    dps_temp->getEvent(&temp_event);
    Serial.print(F("Temperature = "));
    Serial.print(temp_event.temperature);
    Serial.println(" *C");
    Serial.println();
  }

  // Reading pressure also reads temp so don't check pressure
  // before temp!
  if (dps.pressureAvailable()) {
    dps_pressure->getEvent(&pressure_event);
    Serial.print(F("Pressure = "));
    Serial.print(pressure_event.pressure);
    Serial.println(" hPa"); 
  }
}

void printBMP3XX()
{
  if (! bmp3xx.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }
  Serial.print("Temperature = ");
  Serial.print(bmp3xx.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bmp3xx.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");
}

void setup() {
  Serial.begin(9600);

  detectBarometer();
}

void loop() {
  if (detectedBarometer == BME280) {
    printBME();
  } else if (detectedBarometer == BMP085) {
    printBMP();
  } else if (detectedBarometer == DPS310) {
    printPPS310();
  } else if (detectedBarometer == BMP3XX) {
    printBMP3XX();
  }
  
  delay(2000); // Wait for 2 seconds before reading again
}