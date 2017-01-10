/*
* File: Payload.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: December 24th, 2016
*
* Description: Implementation of Payload class's interface.
*
*/
/**************************************************************************************************/
#include "Command.h"
/**************************************************************************************************/

Command::Command()
{
	update = false;
	priority =  NORMAL;
	dataPacket[0] = 0;
	dataPacket[1] = 0;
	dataPacket[2] = 0;
}

/**************************************************************************************************/
Command::~Command()
{
}
/**************************************************************************************************/
Command::Command(bool update, int priority, unsigned char dataPacket[])
{
	this->update = update;
	this->priority = priority;
	this->dataPacket[0] = dataPacket[0];
	this->dataPacket[1] = dataPacket[1];
	this->dataPacket[2] = dataPacket[2];
}
/**************************************************************************************************/
void Command::updateDataPacket(unsigned char control, unsigned char config, unsigned char command)
{
	dataPacket[0] = control;
	dataPacket[1] = config;
	dataPacket[2] = command;

	mode =	       (control & 0xF0) >> 4;
	priority =     (control & 0x0F);
	select =       (config & 0xF0) >> 4;
	this->config = (config & 0x0F);
	this->command = command;
}
/**************************************************************************************************/
bool Command::isUpdate()
{
	return update;
}
/**************************************************************************************************/
void Command::setUpdate(bool update)
{
	this->update = update;
}

/**************************************************************************************************/
void Command::setDataPacket(unsigned char newPacket[])
{
	// this->dataPacket[0] = newPacket[0];
	// this->dataPacket[1] = newPacket[1];
	// this->dataPacket[2] = newPacket[2];
	updateDataPacket(newPacket[0], newPacket[1], newPacket[2]);
}
/**************************************************************************************************/
void Command::setCommandData()
{
	mode =	       (dataPacket[0] & 0xF0) >> 4;
	priority =     (dataPacket[0] & 0x0F);
	select =       (dataPacket[1] & 0xF0) >> 4;
	config = 			 (dataPacket[1] & 0x0F);
	command =      dataPacket[2];
}
/**************************************************************************************************/
// void Command::print()
// {
// 	printf("\nData Packet: %i %i", dataPacket.at(0), dataPacket.at(1));
// 	printf("\nData Packet (hex): %x %x\n", dataPacket.at(0), dataPacket.at(1));
// 	cout << "mode: " << mode << " priority: " << priority << endl;
// 	cout << "select: " << select << " config: " << config << endl;
// 	cout << "command: " << command << endl;
// 	printf("command: %i\n", command);
// }
/**************************************************************************************************/
