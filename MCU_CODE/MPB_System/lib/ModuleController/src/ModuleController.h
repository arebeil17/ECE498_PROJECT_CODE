#ifndef MODULECONTROLLER_H
#define MODULECONTROLLER_H
/*************/
/*
* File: ModuleController.h
* Author: Andres Rebeil
* NetID: andres07
*  Date: January 3rd, 2017
*
* Description: This header file contains the ModuleController class's interface.
*/

/**************************************************************************************************/
#include "stdlib.h"
#include "math.h"
#include "Command.h"
#include <Module.h>
#include <Identify.h>
#include <Keywords.h>
#include <Timer.h>
/**************************************************************************************************/

using namespace std;

class ModuleController {
	private:

	public:
		Timer mainTimer;
		Timer moduleTimer1;
		Timer moduleTimer2;
		Timer moduleTimer3;
		Identify id;
		Module module[NUM_MODULES];

		ModuleController();
		//Getters and setters for all private members

};

#endif // MODULECONTROLLER_H
