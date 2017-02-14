#ifndef SUBCOMMAND_H
#define SUBCOMMAND_H
/*************/
/*
* File: SubCommand.h
* Author: Andres Rebeil
* NetID: andres07
* Date: January 16th, 2017
*
* Description: This header file contains the SubCommand class's interface.
*/

/**************************************************************************************************/
#include "stdlib.h"
#include "math.h"
/**************************************************************************************************/

using namespace std;

class SubCommand {

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

		SubCommand();
		//Customer constructor for SubCommand class
		SubCommand( unsigned char dataPacket[]);

		//Update current data packet vector
		void setDataPacket(unsigned char control, unsigned char SubCommand);

		//Getters and setters for SubCommand class private members
		bool isUpdate();
		void setUpdate(bool update);

		void setDataPacket(unsigned char newPacket[]);
		//Updates SubCommand class data with data stored in dataPacket buffer
		void updateCommandData();

	};

#endif // SubCommand_H
