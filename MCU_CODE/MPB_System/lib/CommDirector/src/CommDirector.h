#ifndef COMMDIRECTOR_H
#define COMMDIRECTOR_H
/*************/
/*
* File: CommDirector.h
* Author: Andres Rebeil
* NetID: andres07
* Date: December 28th, 2016
*
* Description: This header file contains the CommDirector class's interface.
*/

/**************************************************************************************************/
#include <Arduino.h>
#include "stdlib.h"
#include "math.h"
#include "Command.h"
#include "Reply.h"
#include "led.h"
/**************************************************************************************************/

using namespace std;

class CommDirector {
	private:


	public:
    Led led;
    Command command;
    Reply   reply;

    CommDirector();

    bool recieve();

    void transmit();

		void startUp();

		void initConfig(int activeSlots, int config1, int config2, int config3);
};

#endif // COMMDIRECTOR_H
