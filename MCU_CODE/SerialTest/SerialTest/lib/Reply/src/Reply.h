#ifndef REPLY_H
#define REPLY_H
/*************/
/*
* File: Reply.h
* Author: Andres Rebeil
* NetID: andres07
* Date: December 26th, 2016
*
* Description: This header file contains the reply class's interface. This class stores all the
* data associated with the bay's status like payload configuration stored in a data packet for
* replying whenever a command is given. This ensures the Pi always knows what the MCU's current
* state is.
*/

/**************************************************************************************************/
#include "stdlib.h"
#include "math.h"
//#include "stdafx.h"
/**************************************************************************************************/

#define EMPTY 0
#define LED 1
#define SOUND 2


using namespace std;

class Reply
{
	private:


	public:
		int status;
		int mode;
		int confirmation;

		int activeSlots;
		int config1;
		int config2;
		int config3;
		unsigned char dataPacket[2];

		Reply();
		~Reply();

		//Sets the reply packet with the current value of all fields/parameters
		void setDataPacket();

		//Sets the reply packet with the specified/given fields
		void setDataPacket(int status, int mode, int confirmation, int activeSlots, int config1, int config2, int config3);

		//Sets the reply packet with the the specified status and config data
		void setDataPacket(unsigned char status, unsigned char config);

};

#endif // REPLY_H
