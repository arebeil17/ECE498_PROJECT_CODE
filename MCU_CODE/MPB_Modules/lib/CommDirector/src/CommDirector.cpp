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
  int size = Serial.available();
  unsigned char buffer[size];

    if(size >= 2){ //Check if serial data available
      //Serial.readBytes(buf, len)
       Serial.readBytes(buffer, size);
       command.setDataPacket(buffer);
       return true;
    }
    return false;
}
/**************************************************************************************************/
//Transmit reply to master control module
void CommDirector::transmit(){
    //Serial.write(buf, len)
    reply.updateReplyData();
    if(!Serial.write(reply.dataPacket, 2)){
    }
    Serial.flush();
}

/**************************************************************************************************/
