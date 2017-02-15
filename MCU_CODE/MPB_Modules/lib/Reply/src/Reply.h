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
    int state;
		int config; // config = 0x(mode << 3 | lcd << 2 | sound << 1 | led)
    bool mode;
    bool lcd;
    bool sound;
    bool led;
		unsigned char status; // 0x(state)(config)
		unsigned char currentCommand;
		unsigned char dataPacket[2];

		Reply();
		//Customer constructor for Reply class
		Reply( unsigned char dataPacket[]);

		//Update current data packet vector
		void setReplyData(unsigned char status, unsigned char currentCommand);

		//Getters and setters for Reply class private members
		bool isUpdate();
		void setUpdate(bool update);

		void setDataPacket(unsigned char newPacket[]);
		//Updates Reply class data with data stored in dataPacket buffer
		void updateReplyData();

};

#endif // REPLY_H
