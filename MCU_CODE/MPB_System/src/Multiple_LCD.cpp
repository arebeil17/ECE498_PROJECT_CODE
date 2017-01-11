/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include <Arduino.h>
#include <CommDirector.h>
#include <led.h>
#include <ModuleController.h>
#include <LCD.h>
#include <Wire.h>
#include <LiquidCrystal.h>


#define REDLITE 2
#define GREENLITE 3
#define BLUELITE 4
// initialize the library with the numbers of the interface pins
                //RS EN DB4 DB5 DB6 DB7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
LiquidCrystal lcd_2(14, 15, 9, 10, 11, 12);

int brightness = 255;

void setBacklight(uint8_t r, uint8_t g, uint8_t b);

void testLCD(LiquidCrystal *lcd);
void delayTest(unsigned int interval, int sel);

void setup() {
    lcd.begin(20, 4);
    lcd_2.begin(20,4);
    pinMode(REDLITE, OUTPUT);
    pinMode(GREENLITE, OUTPUT);
    pinMode(BLUELITE, OUTPUT);
    brightness = 100;
}
void loop() {
    lcd.print("Hello LCD 1");
    delay(10);
    testLCD(&lcd);
    lcd_2.print("Hello LCD 2");
    delay(10);
    testLCD(&lcd_2);
    delayTest(1, 2);
}

void testLCD(LiquidCrystal *lcd){
    lcd->setCursor ( 0, 1 );
    lcd->print("RGB Cycle 1");
    for (int i = 0; i < 255; i++) {
      setBacklight(i, 0, 255-i);
      delay(5);
    }
    lcd->setCursor ( 0, 2 );
    lcd->print("RGB Cycle 2");
    for (int i = 0; i < 255; i++) {
      setBacklight(255-i, i, 0);
      delay(5);
    }
    lcd->setCursor ( 0, 3 );
    lcd->print("RGB Cycle 3");
    for (int i = 0; i < 255; i++) {
      setBacklight(0, 255-i, i);
      delay(5);
    }
    lcd->setCursor(0, 0);
    lcd->clear();
    lcd->print("Full Brightness Test");
    brightness = 255;
    setBacklight(255,255,255);
    delay(2000);
    lcd->clear();
}

void delayTest(unsigned int interval, int sel){
    lcd.clear(); lcd_2.clear();
    if(sel > 1){
        for(uint8_t i = 0; i < 20; i++){
            for(uint8_t j = 0; j < 40; j++){
                lcd.print("->");
                delay(interval);
                lcd_2.print("->");
                delay(interval);
            }
            for(uint8_t k = 0; k < 40; k++){
                lcd.print("<-");
                delay(interval);
                lcd_2.print("<-");
                delay(interval);
            }
       }
       lcd.clear(); lcd_2.clear();
  }
  if(sel > 0){
    lcd.setCursor(0,0); lcd_2.setCursor(0,0);
     for(uint8_t i = 0; i < 4; i++){
         for(uint8_t j = 1; j <= 20; j++){
             lcd.print("->");
             lcd.setCursor ( j-1, i);
             lcd_2.print("->");
             lcd_2.setCursor ( j-1, i);
             delay(interval + 20);
         }
    }
}
    lcd.clear();
    lcd_2.clear();
}

void setBacklight(uint8_t r, uint8_t g, uint8_t b) {
    // normalize the red LED - its brighter than the rest!
    r = map(r, 0, 255, 0, 100);
    g = map(g, 0, 255, 0, 150);
    r = map(r, 0, 255, 0, brightness);
    g = map(g, 0, 255, 0, brightness);
    b = map(b, 0, 255, 0, brightness);
    // common anode so invert!
    r = map(r, 0, 255, 255, 0);
    g = map(g, 0, 255, 255, 0);
    b = map(b, 0, 255, 255, 0);

    analogWrite(REDLITE, r);
    analogWrite(GREENLITE, g);
    analogWrite(BLUELITE, b);
}
