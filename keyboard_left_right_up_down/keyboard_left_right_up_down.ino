#include "M5Cardputer.h"

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextColor(GREEN);
    M5Cardputer.Display.setTextDatum(middle_center);
    M5Cardputer.Display.setTextFont(&fonts::FreeSerifBoldItalic18pt7b);
    M5Cardputer.Display.setTextSize(1);
    M5Cardputer.Display.drawString("Press a direction",
                                   M5Cardputer.Display.width() / 2,
                                   M5Cardputer.Display.height() / 2);
}

void loop() {
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isChange()) {
        if (M5Cardputer.Keyboard.isKeyPressed('/')) {
            M5Cardputer.Display.clear();
            M5Cardputer.Display.drawString("Right Pressed",
                                           M5Cardputer.Display.width() / 2,
                                           M5Cardputer.Display.height() / 2);
        } else if(M5Cardputer.Keyboard.isKeyPressed(',')) {
            M5Cardputer.Display.clear();
            M5Cardputer.Display.drawString("Left Pressed",
                                           M5Cardputer.Display.width() / 2,
                                           M5Cardputer.Display.height() / 2);
        }else if (M5Cardputer.Keyboard.isKeyPressed(';')) {
            M5Cardputer.Display.clear();
            M5Cardputer.Display.drawString("Up Pressed",
                                           M5Cardputer.Display.width() / 2,
                                           M5Cardputer.Display.height() / 2);
        }else if (M5Cardputer.Keyboard.isKeyPressed('.')) {
            M5Cardputer.Display.clear();
            M5Cardputer.Display.drawString("Down Pressed",
                                           M5Cardputer.Display.width() / 2,
                                           M5Cardputer.Display.height() / 2);
        }
         else {
            M5Cardputer.Display.clear();
            M5Cardputer.Display.drawString("Press a direction",
                                           M5Cardputer.Display.width() / 2,
                                           M5Cardputer.Display.height() / 2);
        }
    }
}
