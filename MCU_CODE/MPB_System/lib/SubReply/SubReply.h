#ifndef SUBREPLY_H
#define SUBREPLY_H
/*************/
/*
* File: SubReply.h
* Author: Andres Rebeil
* NetID: andres07
* Date: January 16th, 2017
*
* Description: This header file contains the SubReply class's interface.
*/

/**************************************************************************************************/
#include "stdlib.h"
#include "math.h"
#include <Keywords.h>
/**************************************************************************************************/

using namespace std;

class SubReply {

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

		SubReply();
		//Customer constructor for SubReply class
		SubReply( unsigned char dataPacket[]);

		//Update current data packet vector
		void setDataPacket(unsigned char status, unsigned char currentCommand);

		//Getters and setters for SubReply class private members
		bool isUpdate();
		void setUpdate(bool update);

		void setReplyData(unsigned char newPacket[]);
		//Updates SubReply class data with data stored in dataPacket buffer
		void updateReplyData();


	};

#endif // SubReply_H
