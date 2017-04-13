/*
* File: Display_Module.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 10th, 2017
*
* Description: Implementation of Display_Module class's interface.
*
*/
/**************************************************************************************************/
#include "Display_Module.h"
/**************************************************************************************************/
Display_Module::Display_Module()
{
    moduleType = LCD_MODULE;
    standard = 3000;
    maxSteps = 1000;
}
/**************************************************************************************************/
void Display_Module::initDisplay(){
    pinMode(REDLITE, OUTPUT);
    pinMode(GREENLITE, OUTPUT);
    pinMode(BLUELITE, OUTPUT);
}
/**************************************************************************************************/
bool Display_Module::simultaneousFunction(uint16_t command, uint16_t step){

      switch(command)
      {   case NO_COMMAND: maxSteps = standard;
              if(rainbow(step)) return true;
          break;
          case SIMULT_FUNCTION_1: maxSteps = 25000;
            if(infoColor(step, BLUE)) return true;
          break;
          case SIMULT_FUNCTION_2: maxSteps = 23500;
            if(infoColor(step, RED)) return true;
          break;
          case SIMULT_FUNCTION_3: maxSteps = 1000;
            if(infoColor(step, GREEN)) return true;
          break;
          case SIMULT_FUNCTION_4: maxSteps = 1000;
            if(infoColor(step, WHITE)) return true;
          break;
          case SIMULT_FUNCTION_5: maxSteps = 1000;
            if(infoColor(step, CORAL)) return true;
          break;
          case SIMULT_FUNCTION_6: maxSteps = 1000;
            if(infoColor(step, PURPLE)) return true;
          break;
          // case INDEPENDENT_FUNCTION_1: maxSteps = 255; return true;
          // case INDEPENDENT_FUNCTION_2: maxSteps = 255; return true;
          // case INDEPENDENT_FUNCTION_3: maxSteps = 255; return true;
          // case INDEPENDENT_FUNCTION_4: maxSteps = 255; return true;
          // case INDEPENDENT_FUNCTION_5: maxSteps = 255; return true;
          // case INDEPENDENT_FUNCTION_6: maxSteps = 255; return true;
          default: return true;
      }
      if(step >= maxSteps) return true;
      else return false;
}
/**************************************************************************************************/
void Display_Module::setBacklight(uint8_t r, uint8_t g, uint8_t b, uint8_t brightness) {
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
/**************************************************************************************************/
bool Display_Module::rainbow(uint16_t step){
    //uint16_t i = step - maxSteps*(step/maxSteps);
    //normalize to 255
    uint16_t i = round(step/(maxSteps*1.0) * 765);
    if(i <= 255) setBacklight(i, 0, 255-i, 255);
    else if(i <= 510) setBacklight(255-i + 255, i - 255, 0, 255);
    else if(i > 510) setBacklight(0, 255-i+ 510, i -510, 255);

    if(step >= maxSteps) return true;
    else return false;
}
/**************************************************************************************************/
bool Display_Module::infoColor(uint16_t step, uint8_t color){
      switch(color){
        case RED:     setBacklight(255, 0, 0, brightness); break;
        case BLUE:    setBacklight(0, 0, 255, brightness); break;
        case GREEN:   setBacklight(0, 255, 0, brightness); break;
        case PURPLE:   setBacklight(255, 64, 255, brightness); break;
        case CORAL:  setBacklight(255, 64, 64, brightness); break;
        case WHITE: setBacklight(255, 255, 255, brightness); break;
      }
      if( step >= maxSteps) return true;
      else return false;
}
