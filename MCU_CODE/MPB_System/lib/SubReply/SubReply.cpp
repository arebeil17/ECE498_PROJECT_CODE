/*
* File: SubSubReply.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 16th, 2017
*
* Description: Implementation of SubSubReply class's interface.
*
*/
/**************************************************************************************************/
#include "SubReply.h"
/**************************************************************************************************/

SubReply::SubReply()
{
  state = 0;
  config = 0;
  mode = 0;
  lcd = false;
  sound = false;
  led = false;
  status = 0;
  currentCommand = 0;
  dataPacket[0] = 0;
  dataPacket[1] = 0;
}

/**************************************************************************************************/
SubReply::SubReply(unsigned char dataPacket[])
{
	this->dataPacket[0] = dataPacket[0];
	this->dataPacket[1] = dataPacket[1];
}
/**************************************************************************************************/
void SubReply::setReplyData(unsigned char status, unsigned char currentCommand)
{
  mode = (status & 0x08);
  lcd = (status & 0x04);
  sound = (status & 0x02);
  led = (status & 0x01);
  this->state = ((status &  0xF0) >> 4);
  this->status = status;
	this->currentCommand = currentCommand;
  dataPacket[0] = status;
	dataPacket[1] = currentCommand;
}

/**************************************************************************************************/
void SubReply::setDataPacket(unsigned char newPacket[])
{
  dataPacket[0] = newPacket[0];
	dataPacket[1] = newPacket[1];

	setReplyData(newPacket[0], newPacket[1]);
}
/**************************************************************************************************/
void SubReply::updateReplyData()
{
  status = (state << 4) | (mode << 3) | (lcd << 2) | (sound << 1) | (led);

  dataPacket[0] = status;
	dataPacket[1] = currentCommand;
}
