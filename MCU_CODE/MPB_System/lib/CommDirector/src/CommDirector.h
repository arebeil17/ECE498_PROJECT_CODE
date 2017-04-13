#ifndef COMMDIRECTOR_H
#define COMMDIRECTOR_H
/*************/
/*
* File: CommDirector.h
* Author: Andres Rebeil
* NetID: andres07
* Date: December 28th, 2016
*
* Description: This header file contains the CommDirector class's interface.
*/

/**************************************************************************************************/
#include <Arduino.h>
#include "stdlib.h"
#include "math.h"
#include "Command.h"
#include "Status.h"
#include "Reply.h"
#include "led.h"
/**************************************************************************************************/
#define START_BYTE 0xCC


using namespace std;

class CommDirector {
	private:

	public:
    Led led;
    Command command;
		Reply reply;
		//SubCommand subCommand[3];
		//Status status[3];


    CommDirector();
		CommDirector(int activeSlots);
		//check for data from Pi and store it
    bool receive();
		//Transmit bay and payload status to Pi
    bool transmit();
		//Receive data from specified payload slot
		bool subReceive(int slot);
		//Transmit currently stored command to specified payload/module slot
		bool subTransmit(int slot);

		void startUp();
		//Initiliazize bay with current configuration
		void initConfig(int activeSlots, int config1, int config2, int config3);
		//Transmit to all active submodules
		int subTransmitAll(bool slot1, bool slot2, bool slot3);
		//Receive data from all active submodules
		bool subReceiveAll(bool slot1, bool slot2, bool slot3);
};

#endif // COMMDIRECTOR_H
