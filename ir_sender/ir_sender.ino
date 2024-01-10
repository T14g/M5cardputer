#define DISABLE_CODE_FOR_RECEIVER 
#define SEND_PWM_BY_TIMER
#define IR_TX_PIN 44

#include "M5Cardputer.h"
#include <IRremote.hpp>  // include the library

int irCommand = 0;

void setup() {
  Serial.begin(9600);
    auto cfg = M5.config();
    M5Cardputer.begin(cfg, true);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextColor(GREEN);
    M5Cardputer.Display.setTextDatum(middle_center);
    M5Cardputer.Display.setTextFont(&fonts::Orbitron_Light_24);
    M5Cardputer.Display.setTextSize(1);

    IrSender.begin(DISABLE_LED_FEEDBACK);  // Start with IR_SEND_PIN as send pin
    IrSender.setSendPin(IR_TX_PIN);
}

void loop() {
    int displayW = M5Cardputer.Display.width() / 2;
    int displayH = M5Cardputer.Display.height() / 2;

    M5Cardputer.update();
    M5Cardputer.Display.clear();

    if (M5Cardputer.Keyboard.isChange()) {
      if (M5Cardputer.Keyboard.isKeyPressed('1')) {
        M5Cardputer.Display.drawString("LED 1",  displayW, displayH);
        irCommand = 1;
      } else if(M5Cardputer.Keyboard.isKeyPressed('2')) {
        M5Cardputer.Display.drawString("LED 2",  displayW, displayH);
        irCommand = 2;
      }else if (M5Cardputer.Keyboard.isKeyPressed('3')) {
        M5Cardputer.Display.drawString("TV",  displayW, displayH);
        irCommand = 3;
      }
    }

    if(irCommand == 1) {
      IrSender.sendNEC(0xEF00, 0x5, 0);
      irCommand = 0;
      delay(500);
    }else if(irCommand == 2) {
      IrSender.sendNEC(0x0, 0x9, 0);
      irCommand = 0;
      delay(500);
    }else if(irCommand == 3) {
      IrSender.sendPanasonic(0x8, 0x3D, 0);
      irCommand = 0;
      delay(500);
    }else {
      M5Cardputer.Display.drawString("Press 1,2 or 3",  displayW, displayH);
    }
    delay(500);
}
