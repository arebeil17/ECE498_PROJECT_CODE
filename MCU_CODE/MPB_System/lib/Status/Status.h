#ifndef Status_H
#define Status_H
/*************/
/*
* File: Status.h
* Author: Andres Rebeil
* NetID: andres07
* Date: January 16th, 2017
*
* Description: This header file contains the Status class's interface. This class stores all the
* data associated with the bay's status like payload configuration stored in a data packet for
* Statusing whenever a command is given. This ensures the Pi always knows what the MCU's current
* state is.
*/

/**************************************************************************************************/
#include "stdlib.h"
#include "math.h"

/**************************************************************************************************/

#define EMPTY 0
#define LED 1
#define SOUND 2


using namespace std;

class Status
{
	private:


	public:
		int status;
		bool initial;
    bool abort;
    bool busy;
    bool idle;
    bool mode;
    bool lcd;
    bool sound;
    bool led;
    unsigned char command;
		unsigned char dataPacket[2];

		Status();

		//Sets the Status packet with the current value of all fields/parameters
		void setDataPacket();

		//Sets the Status packet with the the specified status and config data
		void setDataPacket(unsigned char status, unsigned char command);

};

#endif // Status_H
