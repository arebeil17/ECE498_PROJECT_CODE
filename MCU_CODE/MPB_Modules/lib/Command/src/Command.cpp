/*
* File: SubCommand.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 16th, 2017
*
* Description: Implementation of SubCommand class's interface.
*
*/
/**************************************************************************************************/
#include "Command.h"
/**************************************************************************************************/

Command::Command()
{
  mode = 0;
  hiPriority = false;
  control = 0;
  abort = false;
  reset = false;
  sleep = false;
  repeat = false;
  command = 0;
  dataPacket[0] = 0;
  dataPacket[1] = 0;
}

/**************************************************************************************************/
Command::Command(unsigned char dataPacket[])
{
	this->dataPacket[0] = dataPacket[0];
	this->dataPacket[1] = dataPacket[1];
}
/**************************************************************************************************/
void Command::setDataPacket(unsigned char control, unsigned char command)
{
	dataPacket[0] = control;
	dataPacket[1] = command;

  hiPriority = (control & 0x40);
	mode = (control & 0x30);
  abort = (control & 0x08);
  reset = (control & 0x04);
  sleep = (control & 0x02);
  repeat = (control & 0x01);
  this->control = control;
	this->command = command;
}

/**************************************************************************************************/
void Command::setDataPacket(unsigned char newPacket[])
{
	setDataPacket(newPacket[0], newPacket[1]);
}
/**************************************************************************************************/
void Command::updateCommandData()
{
  control = (mode << 4) | (abort << 3) | (reset << 2) | (sleep << 1) | (repeat);

  dataPacket[0] = control;
	dataPacket[1] = command;
}
