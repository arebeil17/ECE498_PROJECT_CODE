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
/**************************************************************************************************/

using namespace std;

class Module {
	private:

	public:
		int id;
		int state;
		Command command;
		bool idle;
		int mode;
		int config;

		Module();

		//Initialize module as an LED Strip Payload, specify slot position
		bool initLedStrip(unsigned int slot);
		//Initialize module as an LCD Payload, specify slot position
		bool initLCD(unsigned int slot);
		//Initialize module as a SOUND Payload, specify slot position
		bool initSound(unsigned int slot);
};

#endif // MODULE_H
