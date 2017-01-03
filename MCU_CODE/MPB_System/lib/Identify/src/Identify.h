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
#include <String.h>
/**************************************************************************************************/
#define ROOT_PIN 23
#define SLOT_COUNT 1
#define PORT_COUNT 3

#define NO_MODULE 0
#define LED_MODULE 1
#define SOUND_MODULE 2
#define LCD_MODULE 4

using namespace std;

class Identify {
  private:
    int slotId[SLOT_COUNT];

  public:
    int port[PORT_COUNT];

    Identify();

    bool readPorts();

    int getSlotId(int slot);

    String getModuleName(int slot);

};

#endif // IDENTIFY_H
