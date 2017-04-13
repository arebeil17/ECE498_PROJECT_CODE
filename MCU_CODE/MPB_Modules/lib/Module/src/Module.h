#ifndef MODULE_H
#define MODULE_H
/*************/
/*
* File: Module.h
* Author: Andres Rebeil
* NetID: andres07
* Date: January 3, 2017
*
* Description: This header file contains the payload class's interface.
*/

/**************************************************************************************************/
#include <Arduino.h>
#include "stdlib.h"
#include "math.h"
#include "Command.h"
#include "Keywords.h"
#include <Adafruit_NeoPixel.h>
//#include <Display_Module.h>
//#include <LED_Module.h>
//#include <Sound_Module.h>
/**************************************************************************************************/

using namespace std;

class Module {
	private:

	public:
		uint8_t moduleType;
		uint16_t standard;
		uint16_t maxSteps;

		Module();

		Module(uint8_t moduleType);


};

#endif // MODULE_H
