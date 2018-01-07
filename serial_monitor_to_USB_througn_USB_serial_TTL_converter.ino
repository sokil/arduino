int keyboardByte;

void setup() {
  Serial.begin(115200);

}

void loop() {
  if (Serial.available() > 0) {
    keyboardByte = Serial.read();
    Serial.write(keyboardByte);
    Serial.print(keyboardByte);
  }
}
