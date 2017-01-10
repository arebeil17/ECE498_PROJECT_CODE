#ifndef IDENTIFY_H
#define IDENTIFY_H
/*************/
/*
* File: Identify.h
* Author: Andres Rebeil
* NetID: andres07
* Date: January 3rd, 2017
*
* Description: This header file contains the Identify class's interface.
*/
/**************************************************************************************************/
#include <Arduino.h>
#include <string.h>
#include <Module.h>
#include <Keywords.h>
/**************************************************************************************************/
#define ROOT_PIN 23

using namespace std;

class Identify {
  private:
    int slotId[NUM_MODULES];

  public:
    int port[NUM_MODULES*3];

    Identify();

    bool readPorts();

    int getSlotId(int slot);

    String getModuleName(int slot);

};

#endif // IDENTIFY_H
