#ifndef COMMAND_H
#define COMMAND_H
/*************/
/*
* File: Command.h
* Author: Andres Rebeil
* NetID: andres07
* Date: December 24th, 2016
*
* Description: This header file contains the command class's interface.
*/

/**************************************************************************************************/
#include "stdlib.h"
#include "math.h"
#include <Keywords.h>
/**************************************************************************************************/

using namespace std;

class Command {
		private:

		public:
	    int control;
			int mode;
			bool hiPriority;
	    bool abort;
	    bool reset;
	    bool sleep;
	    bool repeat;
			unsigned char command;
			unsigned char dataPacket[2];

			Command();
			//Customer constructor for Command class
			Command( unsigned char dataPacket[]);

			//Update current data packet vector
			void setDataPacket(unsigned char control, unsigned char Command);

			//Getters and setters for Command class private members
			bool isUpdate();
			void setUpdate(bool update);

			void setDataPacket(unsigned char newPacket[]);
			//Updates Command class data with data stored in dataPacket buffer
			void updateCommandData();
			//reset
			void clear();
	};

#endif // COMMAND_H
