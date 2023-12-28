#include "M5Cardputer.h"

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg);
    M5Cardputer.Display.setTextSize(2);  // Adjust the text size if needed
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setCursor(50, 50);  // Set the cursor position
    M5Cardputer.Display.print("Hello, World!");
}

void loop() {

}