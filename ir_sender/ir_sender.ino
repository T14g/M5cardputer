#define DISABLE_CODE_FOR_RECEIVER  // Disables restarting receiver after each
                                   // send. Saves 450 bytes program memory and
                                   // 269 bytes RAM if receiving functions are
                                   // not use


// #define ENABLE_NEC2_REPEATS

#define SEND_PWM_BY_TIMER
#define IR_TX_PIN 44

#include "M5Cardputer.h"
#include <IRremote.hpp>  // include the library

bool enviar = true;

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


    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isChange()) {
        if (M5Cardputer.Keyboard.isKeyPressed('/')) {
            M5Cardputer.Display.clear();
            M5Cardputer.Display.drawString("Right Pressed",
                                           M5Cardputer.Display.width() / 2,
                                           M5Cardputer.Display.height() / 2);

                                            IrSender.sendNEC(0xEF00 , 0x5 , 40700);
   
      // enviar = false;
         delay(500);
                                      


        }else {
           M5Cardputer.Display.clear();
        }
    }

    Serial.println("hello world");
}
