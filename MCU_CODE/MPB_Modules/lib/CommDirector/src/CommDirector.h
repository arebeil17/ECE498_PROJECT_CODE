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
#include "Reply.h"
/**************************************************************************************************/
#define START_BYTE 0xCC

using namespace std;

class CommDirector {
	private:

	public:
    Command command;
    Reply   reply;

    CommDirector();
		//Recieves command from master control module
    bool receive();
		//Transmit reply to master control module
    void transmit();
		//Setup for transmit after command received
		void stageTransmit(uint8_t state, uint8_t config, uint8_t currentCommand);

};

#endif // COMMDIRECTOR_H
