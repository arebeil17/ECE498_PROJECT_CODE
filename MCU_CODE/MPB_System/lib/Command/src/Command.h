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
#include "SubCommand.h"
#include <Keywords.h>
/**************************************************************************************************/

using namespace std;

class Command {

	private:
		bool updated;

	public:
		unsigned char masterControl;
		int mode;
		int config;
		bool hiPriority[3];
		bool slotEnable[3];
		SubCommand subCommand[3];

		Command();
		//Customer constructor for command class
		//Command(bool update, int priority, unsigned char dataPacket[]);

		//Update current data packet vector
		void updateDataPacket(unsigned char control, unsigned char config, unsigned char command);

		//Getters and setters for Command class private members
		bool isUpdated();
		void setUpdated(bool update);

		void setDataPacket(unsigned char newPacket[]);
		//Updates command class data with data stored in dataPacket buffer
		void updateCommandData();

		//For testing
		//void print();

	};

#endif // COMMAND_H
