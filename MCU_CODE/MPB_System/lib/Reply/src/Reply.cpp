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
	ready = false;
	masterState = 0;
	activeSlots = 0;
	dataPacket[0] = START_BYTE;
	dataPacket[1] = 0;
	dataPacket[2] = 0;
	dataPacket[3] = 0;
	dataPacket[4] = 0;
	dataPacket[5] = 0;
	dataPacket[6] = 0;
	dataPacket[7] = 0;
}
/**************************************************************************************************/
//Set the reply ready to send flag
void Reply::setReady(bool ready){
		this->ready = ready;
}
/**************************************************************************************************/
bool Reply::isReady(){
		return ready;
}
/**************************************************************************************************/
//Updates data packet with current value of all fields/parameters
void Reply::updateDataPacket()
{
	 dataPacket[1] = masterState;
	 dataPacket[2] =  subReply[2].dataPacket[0];
	 dataPacket[3] =  subReply[2].dataPacket[1];
	 dataPacket[4] =  subReply[1].dataPacket[0];
	 dataPacket[5] =  subReply[1].dataPacket[1];
	 dataPacket[6] =  subReply[0].dataPacket[0];
	 dataPacket[7] =  subReply[0].dataPacket[1];
}
/**************************************************************************************************/
//Set specific SubModule Reply Data
bool Reply::setDataPacket(int slot, unsigned char newPacket[]){
		dataPacket[1] = (masterState << 4) | (activeSlots & 0x0F);
		switch(slot){
				case 1:
					dataPacket[7] = newPacket[1];
					dataPacket[6] = newPacket[0];
					subReply[0].setDataPacket(newPacket);
					return true;
				case 2:
					dataPacket[5] = newPacket[1];
					dataPacket[4] = newPacket[0];
					subReply[1].setDataPacket(newPacket);
					return true;
				case 3:
					dataPacket[3] = newPacket[1];
					dataPacket[2] = newPacket[0];
					subReply[2].setDataPacket(newPacket);
					return true;
				default:
					return false;
		}
}
/**************************************************************************************************/
