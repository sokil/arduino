#include <WiFi.h>
#include <esp_wifi.h>

const char* ssid = "ESP32C3_AP";
const char* password = "12345678";  // must be ≥8 chars

static IPAddress apIP(10, 0, 0, 1);
static IPAddress netMsk(255, 255, 255, 0);

void setup() {
  Serial.begin(115200);
  delay(5000);

  Serial.println("\nStarting WiFi Access Point...");

  WiFi.mode(WIFI_AP);


  WiFi.softAPConfig(apIP, apIP, netMsk);

  WiFi.setTxPower(WIFI_POWER_8_5dBm);

  bool success = WiFi.softAP(ssid, password);

  if (success) {
    Serial.println("Access Point started!");
    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());

    //WiFi.scanNetworks(true);

    //esp_wifi_set_protocol(WIFI_IF_AP, WIFI_PROTOCOL_11B | WIFI_PROTOCOL_11G | WIFI_PROTOCOL_11N);
  } else {
    Serial.println("Failed to start Access Point!");
  }
}

void loop() {
  delay(1000);
  Serial.printf("Connected stations: %d\n", WiFi.softAPgetStationNum());
}