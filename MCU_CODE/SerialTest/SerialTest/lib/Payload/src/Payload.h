#ifndef PAYLOAD_H
#define PAYLOAD_H
/*************/
/*
* File: Payload.h
* Author: Andres Rebeil
* NetID: andres07
* Date: December 24th, 2016
*
* Description: This header file contains the payload class's interface.
*/

/**************************************************************************************************/
#include "stdlib.h"
#include "math.h"
#include "Command.h"
//#include "stdafx.h"
/**************************************************************************************************/

using namespace std;

class Payload {
	private:
		int id;
		int state;
		Command command;
		bool idle;
		int mode;
		int config;

	public:
		Payload();
		~Payload();

		//Getters and setters for all private members
		int getId();
		void setId(int id);

		int getState();
		void setState(int State);

		bool isIdle();
		void setIdle(bool idle);

		int getMode();
		void setMode(int mode);

		int getConfig();
		void setConfig(int config);
};

#endif // PAYLAOD_H
