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
    displayed = false;
    scrollCount = 1;
}
/**************************************************************************************************/
void Display_Module::initDisplay(){
    pinMode(REDLITE, OUTPUT);
    pinMode(GREENLITE, OUTPUT);
    pinMode(BLUELITE, OUTPUT);
}
/**************************************************************************************************/
bool Display_Module::simultaneousFunction(uint16_t command, uint16_t step, LiquidCrystal *lcd){

      switch(command)
      {   case NO_COMMAND: maxSteps = standard;
              //rainbow(step);
              displayIdle(lcd, step, 100);
              //teamInfo(lcd, step, 200);
          break;
          case SIMULT_FUNCTION_1: maxSteps = 25000;
             infoColor(step, RED);
          break;
          case SIMULT_FUNCTION_2: maxSteps = 23500;
             infoColor(step, GREEN);
          break;
          case SIMULT_FUNCTION_3: maxSteps = 1000;
            infoColor(step, BLUE);
          break;
          case SIMULT_FUNCTION_4: maxSteps = 1000;
            infoColor(step, WHITE);
          break;
          case SIMULT_FUNCTION_5: maxSteps = 1000;
            infoColor(step, PURPLE);
          break;
          case SIMULT_FUNCTION_6: maxSteps = 1000;
            infoColor(step, CORAL);
          break;
          case SIMULT_FUNCTION_7: maxSteps = 1000;
            rainbow(step);
          break;
          default: return true;
      }
      if(step >= maxSteps){
         lcd->noAutoscroll();
         displayed = false;
         return true;
      }else return false;
}
/**************************************************************************************************/
bool Display_Module::independentFunction(uint16_t command, uint16_t step, LiquidCrystal *lcd)
{
        switch(command)
        {   case NO_COMMAND: maxSteps = standard;
                displayIdle(lcd, step, 100);
            break;
            case INDEPENDENT_FUNCTION_1: maxSteps = 25000;
               teamInfo(lcd, step, 200);
               infoColor(step, RED);
            break;
            case INDEPENDENT_FUNCTION_2: maxSteps = 23500;
               infoColor(step, GREEN);
            break;
            case INDEPENDENT_FUNCTION_3: maxSteps = 1000;
              infoColor(step, BLUE);
            break;
            case INDEPENDENT_FUNCTION_4: maxSteps = 1000;
              infoColor(step, WHITE);
            break;
            case INDEPENDENT_FUNCTION_5: maxSteps = 1000;
              infoColor(step, PURPLE);
            break;
            case INDEPENDENT_FUNCTION_6: maxSteps = 1000;
              infoColor(step, CORAL);
            break;
            default: return true;
        }
        if(step >= maxSteps){
           lcd->noAutoscroll();
           displayed = false;
           return true;
        }else return false;
}
/**************************************************************************************************/
void Display_Module::displayIdle(LiquidCrystal *lcd, uint16_t step, uint16_t every){
    if(!displayed){
       lcd->clear();
       lcd->setCursor(0,0);
       lcd->print("Northrop Grumman");
       setBacklight(0,0,255,255);
       displayed = true;
    }
    if(step%every == 0) lcd->scrollDisplayRight();
}
/**************************************************************************************************/
void Display_Module::teamInfo(LiquidCrystal *lcd, uint16_t step, uint16_t every){
  if(step%every == 0){
     scrollCount++;
     displayed = false;
  }
  if(scrollCount > 6) scrollCount = 1;
  if(!displayed){
     char teamInfo[7][20] = { {"Majors:"}, {"Taylor  - SYE"}, {"Stephan - ME"},
                          {"Soosan  - ME"}, {"Andres  - ECE"}, {"Tristan - ME"},
                          {"Johann  - ME"}};
     char current[4][20];
     if(scrollCount < 5){
          strcpy(current[0], teamInfo[0]);
          strcpy(current[1], teamInfo[scrollCount]);
          strcpy(current[2], teamInfo[scrollCount+1]);
          strcpy(current[3], teamInfo[scrollCount+2]);
     }else if(scrollCount < 6) {
          strcpy(current[0], teamInfo[0]);
          strcpy(current[1], teamInfo[scrollCount]);
          strcpy(current[2], teamInfo[scrollCount+1]);
          strcpy(current[3], teamInfo[1]);
     }else{
          strcpy(current[0], teamInfo[0]);
          strcpy(current[1], teamInfo[scrollCount]);
          strcpy(current[2], teamInfo[1]);
          strcpy(current[3], teamInfo[2]);
     }

     displayString(lcd, current, 4);
     setBacklight(0,0,255,255);
     displayed = true;
  }
}
/**************************************************************************************************/
void Display_Module::displayString(LiquidCrystal *lcd, char text[][20], uint8_t rows){
    if(!displayed){
       lcd->clear();
       char temp[21];
       for(int i = 0; i < rows; i++){
           lcd->setCursor(0,i);
           memset(temp, '\0', sizeof(temp));
           strcpy(temp, text[i]);
           lcd->print(temp);
       }
       displayed = true;
    }
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
void Display_Module::rainbow(uint16_t step){
    //uint16_t i = step - maxSteps*(step/maxSteps);
    //normalize to 255
    uint16_t i = round(step/(maxSteps*1.0) * 765);
    if(i <= 255) setBacklight(i, 0, 255-i, 255);
    else if(i <= 510) setBacklight(255-i + 255, i - 255, 0, 255);
    else if(i > 510) setBacklight(0, 255-i+ 510, i -510, 255);
}
/**************************************************************************************************/
void Display_Module::infoColor(uint16_t step, uint8_t color){
      switch(color){
        case RED:     setBacklight(255, 0, 0, brightness); break;
        case BLUE:    setBacklight(0, 0, 255, brightness); break;
        case GREEN:   setBacklight(0, 255, 0, brightness); break;
        case PURPLE:   setBacklight(255, 64, 255, brightness); break;
        case CORAL:  setBacklight(255, 64, 64, brightness); break;
        case WHITE: setBacklight(255, 255, 255, brightness); break;
      }
}
