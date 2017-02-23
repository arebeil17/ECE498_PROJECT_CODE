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
#include "SubReply.h"
/**************************************************************************************************/

#define EMPTY 0
#define LED 1
#define SOUND 2
#define START_BYTE 0xCC

using namespace std;

class Reply
{
	private:
		bool ready;

	public:
		unsigned char masterState;
		unsigned int activeSlots;
		SubReply subReply[3];
		unsigned char dataPacket[8];

		Reply();
		//Set the reply ready to send flag
		void setReady(bool ready);
		//Returns ready flag
		bool isReady();
		//Sets the reply packet with the current value of all fields/parameters
		void updateDataPacket();
		//Set specific SubModule Reply Data
		bool setDataPacket(int slot, unsigned char newPacket[]);

};

#endif // REPLY_H
