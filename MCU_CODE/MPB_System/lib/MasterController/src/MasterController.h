#ifndef MasterController_H
#define MasterController_H
/*************/
/*
* File: MasterController.h
* Author: Andres Rebeil
* NetID: andres07
*  Date: January 3rd, 2017
*
* Description: This header file contains the MasterController class's interface.
*/

/**************************************************************************************************/
#include "stdlib.h"
#include "math.h"
#include "Command.h"
#include <Module.h>
//#include <Identify.h>
#include <Keywords.h>
#include <Timer.h>
/**************************************************************************************************/

using namespace std;

class MasterController {
	private:
		uint8_t state;
	public:
		Timer mainTimer;
		Timer moduleTimer1;
		Timer moduleTimer2;
		Timer moduleTimer3;
		//Identify id;
		Module module[NUM_MODULES];

		MasterController();
		//Getters and setters for all private members

};

#endif // MasterController_H
