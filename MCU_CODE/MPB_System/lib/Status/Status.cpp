/*
* File: Status.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: December 26th, 2016
*
* Description: Implementation of Status class's interface.
*
*/
/**************************************************************************************************/
#include "Status.h"
/**************************************************************************************************/

Status::Status()
{
  status = 0;
  initial = false;
  abort = false;
  busy = false;
  idle = false;
  mode = false;
  lcd = false;
  sound = false;
  led =false;
  command = 0;
	dataPacket[0] = 0;
	dataPacket[1] = 0;
}

/**************************************************************************************************/
void Status::setDataPacket()
{
	dataPacket[0] = ((initial << 7) | (abort << 6) |(busy << 5) | (idle << 4) | (mode << 3) | (lcd << 2) | (sound << 1) | led);
	dataPacket[1] = command;
}

/**************************************************************************************************/
//Sets the Status packet with the the specified status and config data
void  Status::setDataPacket(unsigned char status, unsigned char command) {
  led = (status & 0x01);
  sound = (status & 0x02);
  lcd = (status & 0x04);
  mode = (status & 0x08);
  idle = (status & 0x10);
  busy = (status & 0x20);
  abort = (status & 0x40);
  initial = (status & 0x80);

	dataPacket[0] = status;
	dataPacket[1] = command;
}
/**************************************************************************************************/
