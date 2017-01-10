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

//#include "stdafx.h"
/**************************************************************************************************/
#define NORMAL 2
#define CRITICAL 3
#define NONE 0


using namespace std;

class Command {

	private:
		bool update;

	public:
		int mode;
		int priority;
		int select;
		int config;
		unsigned char command;
		unsigned char dataPacket[3];

		Command();
		~Command();

		//Customer constructor for command class
		Command(bool update, int priority, unsigned char dataPacket[]);

		//Update current data packet vector
		void updateDataPacket(unsigned char control, unsigned char config, unsigned char command);

		//Getters and setters for Command class private members
		bool isUpdate();
		void setUpdate(bool update);

		void setDataPacket(unsigned char newPacket[]);
		//Updates command class data with data stored in dataPacket buffer
		void setCommandData();

		//For testing
		//void print();

	};

#endif // COMMAND_H
