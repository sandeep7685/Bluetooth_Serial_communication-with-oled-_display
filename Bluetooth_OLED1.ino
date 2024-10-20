//This example code is in the Public Domain (or CC0 licensed, at your option.)
//By Evandro Copercini - 2018
//
//This example creates a bridge between Serial and Classical Bluetooth (SPP)
//and also demonstrate that SerialBT have the same functionalities of a normal Serial

#include "BluetoothSerial.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI   21
#define OLED_CLK   22
#define OLED_DC    4
#define OLED_CS    8
#define OLED_RESET 2
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
  

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32test"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");

  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

   Message("Send Text to Display Here...");
  display.display();
  delay(2000);
//  display.clearDisplay();
}

void loop() {
  if (Serial.available()) {
    SerialBT.write(Serial.read());
    Serial.println(Serial.readString());
  }
  
  
  if (SerialBT.available()) {
    String msg=SerialBT.readString();
  Serial.println(msg);
  Message(msg);
  }
  delay(20);
}

int Message(String message){

  display.clearDisplay();
  
  display.setTextSize(2); // Draw 1X-scale text
  display.setTextColor(INVERSE);
  display.setCursor(0, 0);
  display.print(message);
  display.display();
  delay(100);
}
