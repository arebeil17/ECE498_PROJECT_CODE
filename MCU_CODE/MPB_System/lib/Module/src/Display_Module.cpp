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

Display_Module::Display_Module(int slot)
{   switch(slot){
        case 1:
            REDLITE = RED_SLOT1_PIN;
            GREENLITE  = GREEN_SLOT1_PIN;
            BLUELITE  = BLUE_SLOT1_PIN;
        break;
        case 2:
            REDLITE = RED_SLOT2_PIN;
            GREENLITE  = GREEN_SLOT2_PIN;
            BLUELITE  = BLUE_SLOT2_PIN;
        break;
        case 3:
            REDLITE = RED_SLOT3_PIN;
            GREENLITE  = GREEN_SLOT3_PIN;
            BLUELITE  = BLUE_SLOT3_PIN;
        break;
        default:
            REDLITE = 0; GREENLITE  = 0; BLUELITE  = 0;
        break;
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
