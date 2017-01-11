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
#include "Adafruit_TPA2016.h"

#define REDLITE 2
#define GREENLITE 3
#define BLUELITE 4
// initialize the library with the numbers of the interface pins
                //RS EN DB4 DB5 DB6 DB7
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
//Adafruit_TPA2016 audioamp = Adafruit_TPA2016();
// you can change the overall brightness by range 0 -> 255
int brightness = 255;

void setBacklight(uint8_t r, uint8_t g, uint8_t b);
Adafruit_TPA2016 audioamp = Adafruit_TPA2016();

void setup() {
    Serial.begin(9600);


    Serial.println("TPA2016 Audio Test");
    audioamp.begin();
    audioamp.setGain(20);
    // set up the LCD's number of rows and columns:
    lcd.begin(20, 4);
    // Print a message to the LCD.
    lcd.print("RGB 20x4 Display ");
    lcd.setCursor(0,1);
    lcd.print(" Multicolor LCD ");
    pinMode(REDLITE, OUTPUT);
    pinMode(GREENLITE, OUTPUT);
    pinMode(BLUELITE, OUTPUT);
    brightness = 100;
}
void loop() {
        lcd.clear();
        lcd.setCursor ( 0, 0 );
        lcd.print("Running");
        lcd.setCursor ( 0, 1 );
        lcd.print("RGB Cycle 1");
        for (int i = 0; i < 255; i++) {
          setBacklight(i, 0, 255-i);
          delay(5);
        }
        lcd.setCursor ( 0, 2 );
        lcd.print("RGB Cycle 2");
        for (int i = 0; i < 255; i++) {
          setBacklight(255-i, i, 0);
          delay(5);
        }
        lcd.setCursor ( 0, 3 );
        lcd.print("RGB Cycle 3");
        for (int i = 0; i < 255; i++) {
          setBacklight(0, 255-i, i);
          delay(5);
        }
        setBacklight(255,255,255);
        delay(2000);
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
    //Serial.print("R = "); Serial.print(r, DEC);
    //Serial.print("G = "); Serial.print(g, DEC);
    //Serial.print("B = "); Serial.println(b, DEC);
    analogWrite(REDLITE, r);
    analogWrite(GREENLITE, g);
    analogWrite(BLUELITE, b);
}
