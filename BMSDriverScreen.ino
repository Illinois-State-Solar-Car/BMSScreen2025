/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1305 drivers

  Pick one up today in the adafruit shop!
  ------> https://www.adafruit.com/products/2675

These displays use SPI or I2C to communicate, 3-5 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen below must be included in any redistribution
*********************************************************************/

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1325.h>

// Used for software SPI

// Used for software or hardware SPI
#define OLED_CS 21
#define OLED_DC 14

// Used for I2C or SPI
#define OLED_RESET 15

// software SPI
//Adafruit_SSD1305 display(128, 32, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
// hardware SPI - use 7Mhz (7000000UL) or lower because the screen is rated for 4MHz, or it will remain blank!
Adafruit_SSD1325 display(OLED_DC, OLED_RESET, OLED_CS);

double voltage = 35.0;
double current = 96.0;
double max_v = 4.20;
double min_v = 4.19;

double ampHours = 85.7;
double max_temp = 82.3;
double min_temp = 81.3;

double batteryPercentage = 0.99;
int delayTime = millis();

void setup()   {                
  Serial.begin(9600);
  Serial.println("SSD1325 OLED test");
  
  
  display.begin();

  // init done
  //display.display(); // show splashscreen
  delay(1000);
  display.clearDisplay();   // clears the screen and buffer
}


void loop() {
  display.clearDisplay();
  updateVoltage();
  updateCurrent();

  if (millis() - delayTime >= 2500) {
    updateTemps();
  }
  else {
    updateCells();
  }

  if (millis() - delayTime >= 5000) {
    delayTime = millis();
  }
  delay(100);
  display.display();
  current += 1;
  voltage += 1;
  max_v += 0.1;
  min_v += 0.1;
  max_temp += 0.1;
  min_temp += 0.1;

}



void updateCurrent() {
  display.setTextSize(3);
  display.setTextWrap(false);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("C:"+ String(current,1));
}

void updateVoltage() {
  display.setTextSize(3);
  display.setTextWrap(false);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("V:"+ String(voltage,1));
}

void updateTemps() {
  display.setTextSize(1);
  display.setTextWrap(false);
  display.setTextSize(WHITE);
  display.setCursor(0, 56);
  display.print("Hi T:");
  display.print(max_temp,1);
  display.print(" Lo T:");
  display.print(min_temp,1);
}

void updateCells() {
  display.setTextSize(1);
  display.setTextWrap(false);
  display.setTextSize(WHITE);
  display.setCursor(0, 56);
  display.print("Hi V:");
  display.print(max_v,1);
  display.print(" Lo V:");
  display.print(min_v,1);
}

