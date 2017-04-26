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
Display_Module::Display_Module(){
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
bool Display_Module::simultaneousFunction(uint16_t command, uint16_t step, LiquidCrystal *lcd)
{
    switch(command)
      {   case NO_COMMAND: maxSteps = standard;
              //rainbow(step);
              displayIdle(step, 100, lcd);
              //cycleNumber(step, 300 ,lcd);
              //displayNumber(1, lcd);
              //teamInfo(step, 200, lcd);
              //payloadInfo(lcd);
              //manufacturingInfo(lcd);
              //mentorInfo(step, 200, lcd);
              //projectInfo(lcd);
          break;
          case SIMULT_FUNCTION_1: maxSteps = standard;
             infoColor(step, RED);
             displayNumber(1, lcd);
          break;
          case SIMULT_FUNCTION_2: maxSteps = standard;
             infoColor(step, GREEN);
             displayNumber(2, lcd);
          break;
          case SIMULT_FUNCTION_3: maxSteps = standard;
            infoColor(step, BLUE);
            displayNumber(3, lcd);
          break;
          case SIMULT_FUNCTION_4: maxSteps = standard;
            infoColor(step, WHITE);
            displayNumber(4, lcd);
          break;
          case SIMULT_FUNCTION_5: maxSteps = standard;
            infoColor(step, PURPLE);
            displayNumber(5, lcd);
          break;
          case SIMULT_FUNCTION_6: maxSteps = standard;
            infoColor(step, CORAL);
            displayNumber(6, lcd);
          break;
          case SIMULT_FUNCTION_7: maxSteps = standard;
            rainbow(step);
            projectInfo(lcd);
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
                displayIdle(step, 100, lcd);
            break;
            case INDEPENDENT_FUNCTION_1: maxSteps = 25000;
                if(step <= 1) infoColor(step, RED);
                teamInfo(step, 200, lcd);
            break;
            case INDEPENDENT_FUNCTION_2: maxSteps = 23500;
                if(step <= 1) infoColor(step, GREEN);
                mentorInfo(step, 200, lcd);
            break;
            case INDEPENDENT_FUNCTION_3: maxSteps = standard;
               if(step <= 1) infoColor(step, BLUE);
               payloadInfo(lcd);
            break;
            case INDEPENDENT_FUNCTION_4: maxSteps = standard;
               if(step <= 1) infoColor(step, WHITE);
               manufacturingInfo(lcd);
            break;
            case INDEPENDENT_FUNCTION_5: maxSteps = standard;
               if(step <= 1) infoColor(step, PURPLE);
               projectInfo(lcd);
            break;
            case INDEPENDENT_FUNCTION_6: maxSteps = standard;
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
void Display_Module::displayIdle(uint16_t step, uint16_t every, LiquidCrystal *lcd){
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
void Display_Module::teamInfo(uint16_t step, uint16_t every, LiquidCrystal *lcd){
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
  }
}
/**************************************************************************************************/
void Display_Module::payloadInfo(LiquidCrystal *lcd){
    if(!displayed){
      char payloadInfo[4][20] = { {"Payloads:"},
                                  {"- LED"},
                                  {"- LCD"},
                                  {"- SOUND"}};
      //setBacklight(0,0,255,255);
      displayString(lcd, payloadInfo, 4);
    }
}
/**************************************************************************************************/
void Display_Module::mentorInfo(uint16_t step, uint16_t every, LiquidCrystal *lcd){
    if(step%every == 0){
       scrollCount++;
       displayed = false;
    }
    if(scrollCount > 4) scrollCount = 1;
    if(!displayed){               //--------------------
      char mentorInfo[5][20] = { {"Mentor & Sponsors:"},
                                  {"Bob Messenger"},
                                  {"Kyle Klouda"},
                                  {"Dana Cordova"},
                                  {"Christian Esbril"}};
      char current[5][20];
      if(scrollCount < 3){
           strcpy(current[0], mentorInfo[0]);
           strcpy(current[1], mentorInfo[scrollCount]);
           strcpy(current[2], mentorInfo[scrollCount+1]);
           strcpy(current[3], mentorInfo[scrollCount+2]);
      }else if(scrollCount < 4) {
           strcpy(current[0], mentorInfo[0]);
           strcpy(current[1], mentorInfo[scrollCount]);
           strcpy(current[2], mentorInfo[scrollCount+1]);
           strcpy(current[3], mentorInfo[1]);
      }else{
           strcpy(current[0], mentorInfo[0]);
           strcpy(current[1], mentorInfo[scrollCount]);
           strcpy(current[2], mentorInfo[1]);
           strcpy(current[3], mentorInfo[2]);
      }
      displayString(lcd, current, 4);
      //setBacklight(0,0,255,255);
    }
}
/**************************************************************************************************/
void Display_Module::manufacturingInfo(LiquidCrystal *lcd){
    if(!displayed){
      char manufacturingInfo[4][20] = { {"Manufacturing:"},
                                        {"- CNC Laser Brake"},
                                        {"- CNC Press"},
                                        {"- T2 Anodized"}};
      //setBacklight(0,0,255,255);
      displayString(lcd, manufacturingInfo, 4);
    }
}
/**************************************************************************************************/
void Display_Module::projectInfo(LiquidCrystal *lcd){
    if(!displayed){               //--------------------
      char projectInfo[4][20] = { {"U of Arizona:"},
                                  {"Northrop Grumman"},
                                  {"Senior Design 16056"},
                                  {"MPB for UAV"}};
      //setBacklight(0,0,255,255);
      displayString(lcd, projectInfo, 4);
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
void Display_Module::cycleNumber(uint16_t step, uint16_t every, LiquidCrystal *lcd){
    if(step%every == 0){
       scrollCount++;
       displayed = false;
       if(scrollCount > 6) scrollCount = 0;
    }
    if(!displayed){
      switch (scrollCount) {
        case 1:  displayNumber(1,lcd); break;
        case 2:  displayNumber(2,lcd); break;
        case 3:  displayNumber(3,lcd); break;
        case 4:  displayNumber(4,lcd); break;
        case 5:  displayNumber(5,lcd); break;
        case 6:  displayNumber(6,lcd); break;
        default: displayNumber(0,lcd); break;
      }
    }
}
/**************************************************************************************************/
void Display_Module::displayNumber(uint8_t number, LiquidCrystal *lcd){
    char numInfo[4][20];
    if(!displayed){
       switch(number){
          case 1:              //--------------------
              strcpy(numInfo[0],"         |    _    ");
              strcpy(numInfo[1]," 1       |     |   ");
              strcpy(numInfo[2]," One     |     |   ");
              strcpy(numInfo[3],"         |    _|_  ");
          break;
          case 2:              //--------------------
              strcpy(numInfo[0],"         |   ___  ");
              strcpy(numInfo[1]," 2       |     _|");
              strcpy(numInfo[2]," Two     |   /    ");
              strcpy(numInfo[3],"         |  |___  ");
          break;
          case 3:              //--------------------
              strcpy(numInfo[0],"         |   ___  ");
              strcpy(numInfo[1]," 3       |      | ");
              strcpy(numInfo[2]," Three   |   ---| ");
              strcpy(numInfo[3],"         |   ___| ");
          break;
          case 4:              //--------------------
              strcpy(numInfo[0],"         |        ");
              strcpy(numInfo[1]," 4       |   |  |");
              strcpy(numInfo[2]," Four    |   |__|");
              strcpy(numInfo[3],"         |      |");
          break;
          case 5:              //--------------------
              strcpy(numInfo[0],"         |   ___ ");
              strcpy(numInfo[1]," 5       |  |    ");
              strcpy(numInfo[2]," Five    |   --- ");
              strcpy(numInfo[3],"         |   ___|");
          break;
          case 6:              //--------------------
              strcpy(numInfo[0],"         |   /   ");
              strcpy(numInfo[1]," 6       |  |__  ");
              strcpy(numInfo[2]," Six     |  |  | ");
              strcpy(numInfo[3],"         |  |__| ");
          break;
          default:            //--------------------
              strcpy(numInfo[0],"         |   ___  ");
              strcpy(numInfo[1]," 0       |  |   | ");
              strcpy(numInfo[2]," Zero    |  |   | ");
              strcpy(numInfo[3],"         |  |___| ");
          break;
       }
       displayString(lcd, numInfo, 4);
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
/**************************************************************************************************/
void Display_Module::reset(){
    displayed = false;
    scrollCount = 1;
}
