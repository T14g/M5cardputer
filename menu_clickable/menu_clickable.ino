#define DISABLE_CODE_FOR_RECEIVER 
#define SEND_PWM_BY_TIMER
#define IR_TX_PIN 44

#include "M5Cardputer.h"
#include <IRremote.hpp>  // include the library

int menuPosition = 0;
int currentOption = 1;
int irCommand = 0;
bool selectedMenu = false;

void irSender() {
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
      else if (M5Cardputer.Keyboard.isKeyPressed('a')) {
        M5Cardputer.Display.drawString("M1",  displayW, displayH);
        irCommand = 4;
      }
      else if (M5Cardputer.Keyboard.isKeyPressed('s')) {
        M5Cardputer.Display.drawString("M2",  displayW, displayH);
        irCommand = 5;
      }
      else if (M5Cardputer.Keyboard.isKeyPressed('d')) {
        M5Cardputer.Display.drawString("M3",  displayW, displayH);
        irCommand = 6;
      }
      else if (M5Cardputer.Keyboard.isKeyPressed('f')) {
        M5Cardputer.Display.drawString("M4",  displayW, displayH);
        irCommand = 7;
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
    }else if(irCommand == 4) {
      IrSender.sendNEC(0x0, 0x10, 0);
      irCommand = 0;
      delay(500);
    }else if(irCommand == 5) {
      IrSender.sendNEC(0x0, 0x11, 0);
      irCommand = 0;
      delay(500);
    }else if(irCommand == 6) {
      IrSender.sendNEC(0x0, 0x12, 0);
      irCommand = 0;
      delay(500);
    }else if(irCommand == 7) {
      IrSender.sendNEC(0x0, 0x13, 0);
      irCommand = 0;
      delay(500);
    }else {
      M5Cardputer.Display.drawString("Press 1,2 or 3",  displayW, displayH);
    }
    delay(500);
}

void drawMenuOptions() {
    M5Cardputer.Display.drawString("IR",0 ,0);
    M5Cardputer.Display.drawString("WIFI",0 ,22);
    M5Cardputer.Display.drawString("BLUETOOTH",0 ,42);
    M5Cardputer.Display.drawString("Web Server",0 ,62);
    M5Cardputer.Display.drawString("OTHERS",0 ,82);
}

void drawMenu() {
  M5Cardputer.Display.clear();
  M5Cardputer.Display.fillRect(0, menuPosition, 240, 22, 0x7E0); 
  drawMenuOptions();
}

void setup() {
    auto cfg = M5.config();
    M5Cardputer.begin(cfg);

    M5Cardputer.Display.setTextSize(2);
    M5Cardputer.Display.setRotation(1);
    M5Cardputer.Display.setTextColor(0xFFFF);
    IrSender.begin(DISABLE_LED_FEEDBACK);  // Start with IR_SEND_PIN as send pin
    IrSender.setSendPin(IR_TX_PIN);
    drawMenu();
}

void loop() {

    if(currentOption == 1 && selectedMenu) {
      irSender();
    }else {
      M5Cardputer.update();
      if (M5Cardputer.Keyboard.isChange()) {
          if (M5Cardputer.Keyboard.isKeyPressed(';')) {
            if(currentOption > 1) {
              currentOption--;
              menuPosition -= 22;
              drawMenu();
            }
          }else if (M5Cardputer.Keyboard.isKeyPressed('.')) {
              if(currentOption < 5) {
              currentOption++;
              menuPosition += 22;
              drawMenu();
              }
          }
          }else if (M5Cardputer.Keyboard.isKeyPressed(KEY_ENTER)) {
            M5Cardputer.Display.setRotation(1);
            M5Cardputer.Display.setTextColor(GREEN);
            M5Cardputer.Display.setTextDatum(middle_center);
            M5Cardputer.Display.setTextFont(&fonts::Orbitron_Light_24);
            M5Cardputer.Display.setTextSize(1);
            selectedMenu = true;
          }
    }
}