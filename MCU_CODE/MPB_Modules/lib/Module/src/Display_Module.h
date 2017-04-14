#ifndef DISPLAY_MODULE_H
#define DISPLAY_MODULE_H
/*************/
/*
* File: Display_Module.h
* Author: Andres Rebeil
* NetID: andres07
* Date: January 10th, 2017
*
* Description: This header file contains the Display_Module class's interface.
*/
// initialize the library with the numbers of the interface pins
//                  RS EN DB4 DB5 DB6 DB7
//LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

/**************************************************************************************************/
#include <Arduino.h>
#include <Module.h>
#include <LCD.h>
#include <Wire.h>
#include <String.h>
#include <LiquidCrystal.h>
#include <Keywords.h>
/**************************************************************************************************/
#define REDLITE 9
#define GREENLITE 10
#define BLUELITE 11

using namespace std;

//Display_Module is a Subclass of the Module Superclass
class Display_Module {
    private:

      uint8_t brightness = 255;
    public:
      uint8_t moduleType;
      uint16_t standard;
      uint16_t maxSteps;
      uint8_t scrollCount;
      bool displayed;

      Display_Module();

      void initDisplay();

      void setBacklight(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);

      bool simultaneousFunction(uint16_t command, uint16_t step, LiquidCrystal *lcd);

      bool independentFunction(uint16_t command, uint16_t step, LiquidCrystal *lcd);

      void displayIdle(LiquidCrystal *lcd, uint16_t step, uint16_t every);

      void teamInfo(LiquidCrystal *lcd, uint16_t step, uint16_t every);

      void displayString(LiquidCrystal *lcd, char text[][20], uint8_t rows);

      void rainbow(uint16_t step);

      void infoColor(uint16_t step, uint8_t color);
};

#endif // DISPLAY_MODULE_H
