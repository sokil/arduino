#include <SPI.h>

volatile byte receivedData;
volatile bool dataReceived = false;

unsigned long now = 0;
unsigned long prev_now = 0;

int sck_state = -1;
int cs_state = -1;
int mosi_state = -1;

int current_cs_state = -1;
int current_sck_state = -1;
int current_mosi_state = -1;

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

  Serial.println("SPI Started");
}

ISR(SPI_STC_vect) {
  // Read the received byte from SPI data register
  receivedData = SPDR;
  dataReceived = true;
}

void loop() {
  // handle pin states
  current_cs_state = digitalRead(SS);
  current_sck_state = digitalRead(SCK);
  current_mosi_state = digitalRead(MOSI);

  if (
    current_cs_state != cs_state 
    || current_sck_state != sck_state 
    || current_mosi_state != mosi_state
  ) {
      prev_now = now;
      now = millis();

      if (current_cs_state != cs_state ) {
        cs_state = current_cs_state;
      }

      if (current_sck_state != sck_state) {
        sck_state = current_sck_state;
      }

      if (current_mosi_state != mosi_state) {
        mosi_state = current_mosi_state;
      }

      Serial.print(cs_state == LOW ? "CS=LOW,  " : "CS=HIGH, ");
      Serial.print(sck_state == LOW ? "SCK=LOW,  " : "SCK=HIGH, ");
      Serial.print(mosi_state == LOW ? "MOSI=LOW,  " : "MOSI=HIGH, ");
      Serial.print("Delay=");
      Serial.println(now - prev_now);
  }

  // print data byte
  if (dataReceived) {
    Serial.print("0x");
    if (receivedData < 0x10) {
      Serial.print("0");
    }
    Serial.println(receivedData, HEX);
    Serial.println("");

    dataReceived = false;
  }

  // wait all ports to switch
  // delay(2);
}