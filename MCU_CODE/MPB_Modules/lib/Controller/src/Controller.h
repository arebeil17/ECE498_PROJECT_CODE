#ifndef CONTROLLER_H
#define CONTROLLER_H
/*************/
/*
* File: Controller.h
* Author: Andres Rebeil
* NetID: andres07
*  Date: March 16th, 2017
*
* Description: This header file contains the Controller class's interface.
*/

/**************************************************************************************************/
#include "stdlib.h"
#include "math.h"
#include "Command.h"
#include <Keywords.h>
#include <CommDirector.h>
#include <Display_Module.h>
#include <LED_Module.h>
#include <Sound_Module.h>
#include <Adafruit_NeoPixel.h>
//#include <Identify.h>
/**************************************************************************************************/

using namespace std;

class Controller {
	private:
  		CommDirector commDirector;

	public:
			LED_Module led_Module;
			Display_Module display_Module;
			Sound_Module sound_Module;
			uint8_t moduleType;
			uint8_t state;
			bool stateResolved;
			uint8_t currentCommand;
			uint16_t maxSteps;

			Controller();
			Controller(uint8_t moduleType);
			Controller(uint8_t moduleType, Adafruit_NeoPixel* strip);

			void init(uint8_t moduleType);

			void wait_Routine(uint16_t step);
			void wait_Routine(uint16_t step, Adafruit_NeoPixel* strip);
			void execute_Routine(uint16_t step);
			void execute_Routine(uint16_t step, Adafruit_NeoPixel* strip);
			void receive_Routine();

			void done();
			bool validCommandCheck(uint8_t command);

			void resetMaxStep(uint8_t moduleType);

			bool commandExecution(uint8_t moduleType, uint8_t command, uint16_t step, Adafruit_NeoPixel* strip);
};

#endif // Controller_H
