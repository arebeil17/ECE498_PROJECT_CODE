/*
* File: LED_Module.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 10th, 2017
*
* Description: Implementation of LED_Module class's interface.
*
*/
/**************************************************************************************************/
#include "LED_Module.h"
/**************************************************************************************************/

LED_Module::LED_Module()
{

}
/**************************************************************************************************/
//Initialize module as an LED Payload specify slot position
bool LED_Module::initStrip(unsigned int slot){
		switch(slot){
			case 1:
				strip = Adafruit_NeoPixel(60, LED_SLOT1_PIN, NEO_RGBW  + NEO_KHZ800);
				return true;
			case 2:
				strip = Adafruit_NeoPixel(60, LED_SLOT2_PIN, NEO_RGBW  + NEO_KHZ800);
				return true;
			case 3:
				strip = Adafruit_NeoPixel(60, LED_SLOT3_PIN, NEO_RGBW  + NEO_KHZ800);
				return true;
			default:
				return false;
		}
}
