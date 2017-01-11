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
#include <Module.h>
#include <LCD.h>
#include <Wire.h>
#include <LiquidCrystal.h>
/**************************************************************************************************/

using namespace std;

//Display_Module is a Subclass of the Module Superclass
class Display_Module: public Module {
    private:
      unsigned int REDLITE;
      unsigned int GREENLITE;
      unsigned int BLUELITE;
    public:
      Display_Module(int slot);

      void setBacklight(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness);
};

#endif // DISPLAY_MODULE_H
