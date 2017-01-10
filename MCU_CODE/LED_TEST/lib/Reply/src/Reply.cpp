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

Reply::Reply()
{
	status = 0;
	mode = 0;
	confirmation = 0;

	activeSlots = 0;
	config1 = EMPTY;
	config2 = EMPTY;
	config3 = EMPTY;

	dataPacket[0] = 0;
	dataPacket[1] = 0;
}

/**************************************************************************************************/
Reply::~Reply()
{
}

/**************************************************************************************************/
void Reply::setDataPacket()
{
	dataPacket[0] = ((status << 4) | (mode << 3) | (confirmation));
	dataPacket[1] = ((activeSlots << 6) | (config1 << 4) | (config2 << 2) | (config3));
}
/**************************************************************************************************/
void Reply::setDataPacket(int status, int mode, int confirmation, int activeSlots, int config1, int config2, int config3)
{
	this->status = status;
	this->mode = mode;
	this->confirmation = confirmation;
	this->activeSlots = activeSlots;
	this->config1 = config1;
	this->config2 = config2;
	this->config3 = config3;
	dataPacket[0] = ((status << 4) | (mode << 3) | (confirmation));
	dataPacket[1] = ((activeSlots << 6) | (config1 << 4) | (config2 << 2) | (config3));
}
/**************************************************************************************************/
//Sets the reply packet with the the specified status and config data
void  Reply::setDataPacket(unsigned char status, unsigned char config) {
	this->status = (status & 0xF0) >> 4;
	this->mode = (status & 0x04) >>3;
	this->confirmation = (status & 0x07);
	this->activeSlots = (config & 0xC0) >> 6;
	this->config1 = (config & 0x30) >> 4;
	this->config2 = (config & 0x0C) >> 2;
	this->config3 = (config & 0x03);
	dataPacket[0] = status;
	dataPacket[1] = config;
}
/**************************************************************************************************/
