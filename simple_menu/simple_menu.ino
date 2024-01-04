#include "M5Cardputer.h"

int menuPosition = 0;
int currentOption = 1;

void drawMenuOptions() {
    M5Cardputer.Display.drawString("Menu option1",0 ,0);
    M5Cardputer.Display.drawString("Menu option2",0 ,22);
    M5Cardputer.Display.drawString("Menu option3",0 ,42);
    M5Cardputer.Display.drawString("Menu option4",0 ,62);
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
    drawMenu();
}

void loop() {
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isChange()) {
        if (M5Cardputer.Keyboard.isKeyPressed(';')) {
          if(currentOption > 1) {
            currentOption--;
            menuPosition -= 22;
            drawMenu();
          }
        }else if (M5Cardputer.Keyboard.isKeyPressed('.')) {
            if(currentOption < 4) {
            currentOption++;
            menuPosition += 22;
            drawMenu();
            }
        }
    }
}