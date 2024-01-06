#include "M5Cardputer.h"
#include <WiFi.h>

const int MAX_NETWORKS = 10; // Maximum number of networks to display
int selectedNetwork = 0;     // Index of the selected network
int startIdx = 0;            // Start index for displaying networks

void displayNetworks() {
  M5.Lcd.fillScreen(TFT_BLACK);
  M5.Lcd.setTextColor(TFT_WHITE);
  M5.Lcd.setTextSize(1);

  int numNetworks = WiFi.scanNetworks();
  // if (numNetworks == 0) {
  //   M5.Lcd.println("No WiFi networks found.");
  // } else {
  //   M5.Lcd.println("Available WiFi Networks:");

  //   for (int i = startIdx; i < min(startIdx + MAX_NETWORKS, numNetworks); ++i) {
  //     int yPos = (i - startIdx) * 15; // Adjust the vertical spacing as needed
  //     M5.Lcd.setCursor(10, yPos);
  //     M5.Lcd.printf("%d: %s (RSSI: %d dBm)", i + 1, WiFi.SSID(i).c_str(), WiFi.RSSI(i));
  //   }
  // }

  Serial.println(numNetworks);
}

void setup() {
  M5.begin();
  Serial.begin(115200);

  M5.Lcd.setRotation(1); // Set screen rotation if needed
  displayNetworks();
}

void loop() {
  M5.update();
  int numNetworks = WiFi.scanNetworks();
  // if (M5.BtnA.wasPressed()) {
  //   selectedNetwork = max(0, selectedNetwork - 1);
  //   if (selectedNetwork < startIdx) {
  //     startIdx = selectedNetwork;
  //   }
  //   displayNetworks();
  // }

  // if (M5.BtnA.wasPressed()) {
  //   int numNetworks = WiFi.scanNetworks();
  //   if (numNetworks > 0) {
  //     selectedNetwork = min(selectedNetwork + 1, numNetworks - 1);
  //     if (selectedNetwork >= startIdx + MAX_NETWORKS) {
  //       startIdx = selectedNetwork - MAX_NETWORKS + 1;
  //     }
  //     displayNetworks();
  //   }
  // }
  Serial.println(numNetworks);
}
