/*
* File: Module.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 3, 2017
*
* Description: Implementation of Module class's interface.
*
*/
/**************************************************************************************************/
#include "Module.h"
/**************************************************************************************************/

Module::Module()
{
	id = NO_MODULE;
	state = 0;
	//Command command;
	idle = true;
	mode = 0;
	config = 0;
}
/**************************************************************************************************/
//Initialize module as an LED Payload specify slot position
bool Module::initLedStrip(unsigned int slot){
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
/**************************************************************************************************/
//Initialize module as an LCD Payload specify slot position
bool Module::initLCD(unsigned int slot){
	switch(slot){
		case 1: break;
		case 2: break;
		case 3: break;
		default: return false;
	}
}
/**************************************************************************************************/
//Initialize module as a SOUND Payload specify slot position
bool Module::initSound(unsigned int slot){
	switch(slot){
		case 1: break;
		case 2: break;
		case 3: break;
		default: return false;
	}
}
/**************************************************************************************************/
