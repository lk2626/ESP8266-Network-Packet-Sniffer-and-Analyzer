#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define BUFFER_SIZE 256

WiFiUDP udp;
char packetBuffer[BUFFER_SIZE];

// Set this to your network's SSID and Password
const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

void packetHandler(uint8_t *buffer, uint16_t len) {
  Serial.print("Packet captured: ");
  Serial.print(len);
  Serial.println(" bytes");

  // Extract basic information
  for (int i = 0; i < len; i++) {
    Serial.print(buffer[i], HEX);
    Serial.print(" ");
    if ((i + 1) % 16 == 0) {
      Serial.println();
    }
  }
  Serial.println("\n");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // Station mode
  WiFi.begin(ssid, password);

  Serial.println("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
  
  // Set ESP8266 to promiscuous mode
  wifi_promiscuous_enable(true);
  wifi_set_promiscuous_rx_cb(packetHandler);
}

void loop() {
  // Continuously listen to network packets
  delay(1000);
}
