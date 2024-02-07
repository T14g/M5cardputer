#define DISABLE_CODE_FOR_RECEIVER 
#define SEND_PWM_BY_TIMER
#define IR_TX_PIN 44

#define HAS_SDCARD
#define SD_CLK_PIN 40
#define SD_MISO_PIN 39
#define SD_MOSI_PIN 14
#define SD_CS_PIN 12

#if defined(HAS_SDCARD)
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#endif

bool sdcardMounted = false;

#if defined(HAS_SDCARD)
SPIClass* sdcardSPI = NULL;
SemaphoreHandle_t sdcardSemaphore;
#endif

#include "M5Cardputer.h"
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <IRremote.hpp>  

const char* ssid = "SSID";
const char* password = "PW";

AsyncWebServer server(80);

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
      else if (M5Cardputer.Keyboard.isKeyPressed(';')) {
        M5Cardputer.Display.drawString("Rise bpm",  displayW, displayH);
        irCommand = 8;
      }
      else if (M5Cardputer.Keyboard.isKeyPressed('.')) {
        M5Cardputer.Display.drawString("Drop bpm",  displayW, displayH);
        irCommand = 9;
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
    }else if(irCommand == 8) {
      IrSender.sendNEC(0x0, 0x15, 0);
      irCommand = 0;
      delay(500);
    }else if(irCommand == 9) {
      IrSender.sendNEC(0x0, 0x17, 0);
      irCommand = 0;
      delay(500);
    }else {
      M5Cardputer.Display.drawString("Press 1,2 or 3",  displayW, displayH);
    }
    delay(500);
}

void drawMenuOptions() {
    M5Cardputer.Display.drawString("IR",0 ,0);
    M5Cardputer.Display.drawString("Ir menu 2",0 ,22);
    M5Cardputer.Display.drawString("BLUETOOTH",0 ,42);
    M5Cardputer.Display.drawString("Web Server",0 ,62);
    M5Cardputer.Display.drawString("SD Card",0 ,82);
}

void drawIrMenu() {
    M5Cardputer.update();
    M5Cardputer.Display.clear();
    M5Cardputer.Display.drawString("Led 1",0 ,0);
    M5Cardputer.Display.drawString("Led 2",0 ,22);
    M5Cardputer.Display.drawString("Galaxy projector",0 ,42);
    M5Cardputer.Display.drawString("TV",0 ,62);
    M5Cardputer.Display.drawString("Metronome",0 ,82);
}

void startSDcard() {
  M5Cardputer.update();
  M5Cardputer.Display.clear();

  #if defined(HAS_SDCARD)
  sdcardSemaphore = xSemaphoreCreateMutex();
  sdcardSPI = new SPIClass(FSPI);
  sdcardSPI->begin(SD_CLK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);

  delay(10);

  if (!SD.begin(SD_CS_PIN, *sdcardSPI)) {
    M5Cardputer.Display.print("Fail to load SD");

  } else {
    M5Cardputer.Display.print("SD loaded");
    // sdcardMounted = true;
  }
#endif
}

void drawMenu() {
  M5Cardputer.Display.clear();
  M5Cardputer.Display.fillRect(0, menuPosition - (currentOption + 1), 240, 22, 0x7E0); 
  drawMenuOptions();
}

void createFileSD() {
  File file = SD.open("/test.txt", FILE_APPEND);

  // Check if the file opened successfully
  if (file) {
    // Write to the file
    file.println("Hello, World!");
     M5Cardputer.Display.print("Creating file on SD");

    // Close the file
    file.close();
    Serial.println("File written successfully.");
  } else {
    Serial.println("Error opening the file.");
    M5Cardputer.Display.print("FAil on create file on SD");
  }
}

void serverMode() {
    startSDcard();
    createFileSD();

    M5Cardputer.Display.clear();
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(250);
    }

    if(WiFi.status() == WL_CONNECTED) {
      M5Cardputer.Display.print("Server at:");
      M5Cardputer.Display.print( WiFi.localIP());
    }
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
      File file = SD.open("/html/index.html");
      if (file) {
        M5Cardputer.Display.print("Sending HTML File!");
        request->send(SD, "/html/index.html", "text/html");
        file.close();
      }else{
        M5Cardputer.Display.print("Error to show HTML file");
      }
    });

    server.on("/dist/css/bootstrap.min.css", HTTP_GET, [](AsyncWebServerRequest *request){
      // Replace "your_css_file_path" with the actual path on your SD card
      File file = SD.open("/html/dist/css/bootstrap.min.css");
      if(file) {
          request->send(SD, "/html/dist/css/bootstrap.min.css", "text/css");
      }else{
        M5Cardputer.Display.print("Error to show CSS file");
      }
    });

    server.on("/images/1.jpg", HTTP_GET, [](AsyncWebServerRequest *request){
      // Replace "your_css_file_path" with the actual path on your SD card
      File file = SD.open("/html/images/1.jpg");
      if(file) {
          request->send(SD, "/html/images/1.jpg", "image");
      }else{
        M5Cardputer.Display.print("Error to show Img file");
      }
    });

    server.on("/test", HTTP_POST, [](AsyncWebServerRequest *request){
      String message = request->arg("Count");
      M5Cardputer.Display.print( message);
      M5Cardputer.Speaker.tone(2000, 500);
      request->send(200, "text/plain", "Post received");
    });

    server.on("/saveData", HTTP_POST, [](AsyncWebServerRequest *request){
        M5Cardputer.Display.clear();
        const char* email = "";
        const char* password = "";

        if(request->hasParam("email", true)) {
          AsyncWebParameter* p = request->getParam("email", true);
          email = p->value().c_str();
          M5Cardputer.Display.print(email);
        }

        if(request->hasParam("password", true)) {
          AsyncWebParameter* p = request->getParam("password", true);
          password = p->value().c_str();
          M5Cardputer.Display.println(password);
        }

        File file = SD.open("/html/logged.html");
        if (file) {
          M5Cardputer.Display.print("Sending HTML File!");
          request->send(SD, "/html/logged.html", "text/html");
          file.close();
        }else{
          M5Cardputer.Display.print("Error to show HTML file");
        }
  });


    // Enable CORS
    DefaultHeaders::Instance().addHeader(F("Access-Control-Allow-Origin"), F("*"));
    // server.addHeader("Access-Control-Allow-Origin", "*");
    server.begin();
    selectedMenu = false;
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
    }else if(currentOption == 4 && selectedMenu) {
      serverMode();
    }else if(currentOption == 2 && selectedMenu) {
      drawIrMenu();
      selectedMenu = false;
    }else if(currentOption == 5 && selectedMenu) {
      startSDcard();
      selectedMenu = false;
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
            if(currentOption == 1) {
              M5Cardputer.Display.setRotation(1);
              M5Cardputer.Display.setTextColor(GREEN);
              M5Cardputer.Display.setTextDatum(middle_center);
              M5Cardputer.Display.setTextFont(&fonts::Orbitron_Light_24);
              M5Cardputer.Display.setTextSize(1);
            }
            selectedMenu = true;
          }
    }
}