/*
* File: Reply.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: December 26th, 2016
*
* Description: Implementation of Reply class's interface.
*
*/
/**************************************************************************************************/
#include "Reply.h"
/**************************************************************************************************/

/*
* File: SubReply.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 16th, 2017
*
* Description: Implementation of SubReply class's interface.
*
*/
/**************************************************************************************************/
#include "Reply.h"
/**************************************************************************************************/

Reply::Reply()
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
Reply::Reply(unsigned char dataPacket[])
{
	this->dataPacket[0] = dataPacket[0];
	this->dataPacket[1] = dataPacket[1];
}
/**************************************************************************************************/
void Reply::setReplyData(unsigned char status, unsigned char currentCommand)
{
  mode = (status & 0x08);
  lcd = (status & 0x04);
  sound = (status & 0x02);
  led = (status & 0x01);
  this->state = ((status &  0xF0) >> 4);
	this->currentCommand = currentCommand;
  dataPacket[0] = status;
	dataPacket[1] = currentCommand;
}

/**************************************************************************************************/
void Reply::setDataPacket(unsigned char newPacket[])
{
  dataPacket[0] = newPacket[0];
	dataPacket[1] = newPacket[1];
  status = newPacket[0];
  currentCommand = newPacket[1];

	setReplyData(dataPacket[0], dataPacket[1]);
}
/**************************************************************************************************/
void Reply::updateReplyData()
{
  status = (state << 4) | (mode << 3) | (lcd << 2) | (sound << 1) | (led);

  dataPacket[0] = status;
	dataPacket[1] = currentCommand;
}
