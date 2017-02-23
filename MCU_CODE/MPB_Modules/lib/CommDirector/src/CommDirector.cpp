/*
* File: CommDirector.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: December 28th, 2016
*
* Description: Implementation of CommDirector class's interface.
*
*/
/**************************************************************************************************/
#include "CommDirector.h"
/**************************************************************************************************/
CommDirector::CommDirector(){
    Serial1.begin(38400);
}
/**************************************************************************************************/
//Recieves command from master control module
bool CommDirector::recieve(){
  int size = Serial1.available();
  unsigned char buffer[size];

    if(size >= 3){ //Check if serial data available
      //Serial.readBytes(buf, len)
       Serial1.readBytes(buffer, size);
       if(buffer[0] != START_BYTE) return false;
       command.setDataPacket(buffer[1], buffer[2]);
       return true;
    }
    return false;
}
/**************************************************************************************************/
//Transmit reply to master control module
void CommDirector::transmit(){
    //Serial.write(buf, len)
    reply.updateReplyData();
    unsigned char buffer[3];
    buffer[0] = START_BYTE;
    buffer[1] = reply.dataPacket[0];
    buffer[2] = reply.dataPacket[1];
    //Serial.print("Buffer: "); Serial.print(buffer[0]);
    //Serial.print(" "); Serial.print(buffer[1]);
    //Serial.print(" "); Serial.println(buffer[2]);
    if(!Serial1.write(buffer, 3)){
    }
    Serial1.flush();
}

/**************************************************************************************************/
