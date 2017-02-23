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
Command::Command(){
	updated = false;
	hiPriority[0] = false;
	hiPriority[1] = false;
	hiPriority[2] = false;
}
//**************************************************************************************************/
bool Command::isUpdated(){
	return updated;
}
/**************************************************************************************************/
void Command::setUpdated(bool update){
	updated = update;
}
/**************************************************************************************************/
//Set all command data with given dataPacket
void Command::setDataPacket(unsigned char newPacket[]){

		masterControl = newPacket[0];
		subCommand[0].setDataPacket(newPacket[5], newPacket[6]);
		subCommand[1].setDataPacket(newPacket[3], newPacket[4]);
		subCommand[2].setDataPacket(newPacket[1], newPacket[2]);
		updateCommandData();
}

/**************************************************************************************************/
//Updates command class data with data stored in dataPacket buffer
void Command::updateCommandData(){
		mode = (masterControl & 0xF0) >> 4;
		hiPriority[0] = subCommand[0].hiPriority;
		hiPriority[1] = subCommand[1].hiPriority;
		hiPriority[2] = subCommand[2].hiPriority;
		slotEnable[0] = masterControl & 0x01;
		slotEnable[1] = (masterControl & 0x02) >> 2;
		slotEnable[2] = (masterControl & 0x04) >> 3;
}
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
