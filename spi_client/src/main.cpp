#include <SPI.h>

volatile byte receivedData;
volatile bool dataReceived = false;

// #define PIN_SPI_SS    (10)
// #define PIN_SPI_MOSI  (11)
// #define PIN_SPI_MISO  (12)
// #define PIN_SPI_SCK   (13)

void setup() {
  // Initialize the Serial port for output
  Serial.begin(9600);

  // Set MISO (Master In Slave Out) as OUTPUT
  pinMode(MISO, OUTPUT);

  // Initialize SPI in slave mode
  SPCR |= _BV(SPE);

  // Attach SPI interrupt
  SPI.attachInterrupt();

  Serial.print("SPI Started");
}

ISR(SPI_STC_vect) {
  // Read the received byte from SPI data register
  receivedData = SPDR;
  dataReceived = true;
}

void loop() {
  // If data has been received
  if (dataReceived) {
    // Print the received data in hex format
    Serial.print("Received: 0x");
    if (receivedData < 0x10) {
      Serial.print("0"); // Add leading zero for single hex digit
    }
    Serial.println(receivedData, HEX);

    // Reset the flag
    dataReceived = false;
  }
}