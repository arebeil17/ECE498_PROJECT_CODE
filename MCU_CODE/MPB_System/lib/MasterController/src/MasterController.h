#ifndef MasterController_H
#define MasterController_H
/*************/
/*
* File: MasterController.h
* Author: Andres Rebeil
* NetID: andres07
*  Date: January 3rd, 2017
*
* Description: This header file contains the MasterController class's interface.
*/

/**************************************************************************************************/
#include "stdlib.h"
#include "math.h"
#include "Command.h"
#include <CommDirector.h>
//#include <Identify.h>
#include <Keywords.h>
#include <Timer.h>
/**************************************************************************************************/

using namespace std;

class MasterController {
	private:
		CommDirector commDirector;
	public:
		uint8_t state;
		uint8_t activeCount;
		bool active_Slot1;
		bool active_Slot2;
		bool active_Slot3;
		bool commandReceived;
		bool echoReady;
		bool stateResolved;

		MasterController();

		void identify_Routine(uint8_t calls);
		void wait_Routine();
		void relay_Routine();
		void echo_Routine(uint8_t calls);
		void reply_Routine();

};

#endif // MasterController_H
