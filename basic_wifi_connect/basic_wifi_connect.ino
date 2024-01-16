#include "M5Cardputer.h"
#include <WiFi.h>

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASSWORD";

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg);
    M5Cardputer.Display.setTextSize(2);  // Adjust the text size if needed
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setCursor(50, 50);  // Set the cursor position

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(250);
        Serial.print(".");
    }

    if(WiFi.status() == WL_CONNECTED) {
        M5Cardputer.Display.print("Wifi connected!");
    }
  
}

void loop() {

}