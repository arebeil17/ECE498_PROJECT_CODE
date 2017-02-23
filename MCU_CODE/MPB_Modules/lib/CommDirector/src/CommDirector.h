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
    bool recieve();
		//Transmit reply to master control module
    void transmit();
};

#endif // COMMDIRECTOR_H
