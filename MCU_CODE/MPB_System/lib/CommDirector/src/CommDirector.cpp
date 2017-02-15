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
}
/**************************************************************************************************/
CommDirector::CommDirector(int activeSlots){
    Serial.begin(38400);
    if(activeSlots >= 3) Serial3.begin(38400);
    if(activeSlots >= 2) Serial2.begin(38400);
    if(activeSlots >= 1) Serial1.begin(38400);

}
/**************************************************************************************************/
bool CommDirector::recieve(){
  int size = Serial.available();
  unsigned char buffer[size];

    if(size >= 7){ //Check if serial data available
       led.setLED(RECIEVE);
      //Serial.readBytes(buf, len)
       Serial.readBytes(buffer, size);
       command.setDataPacket(buffer);
       delay(50);
       return true;
    }
    return false;
}
/**************************************************************************************************/
//Transmit bay and payload status to Pi
void CommDirector::transmit(){
    led.setLED(SEND);
    //Serial.write(buf, len)
    reply.updateDataPacket();
    if(!Serial.write(reply.dataPacket, 7)){
      led.setLED(7); //Orange status for no data sent
    }
    Serial.flush();
}
/**************************************************************************************************/
//Recieve data from specified payload slot
bool CommDirector::subRecieve(int slot){
    switch(slot){
      case 1:
        if(!Serial1.readBytes(reply.subReply[0].dataPacket, 2)) return false;
        return true;
      case 2:
        if(!Serial2.readBytes(reply.subReply[1].dataPacket, 2)) return false;
        return true;
      case 3:
        if(!Serial3.readBytes(reply.subReply[2].dataPacket, 2)) return false;
        return true;
      default:
        return false;
    }
}
/**************************************************************************************************/
//Transmit currently stored command to specified payload/module slot
bool CommDirector::subTransmit(int slot){
    switch(slot){
      case 1:
        if(!Serial1.write(command.subCommand[0].dataPacket, 2)) return false;
        return true;
      case 2:
        if(!Serial2.write(command.subCommand[1].dataPacket, 2)) return false;
        return true;
      case 3:
        if(!Serial3.write(command.subCommand[2].dataPacket, 2)) return false;
        return true;
      default:
        return false;
    }
}
/**************************************************************************************************/
void CommDirector::startUp(){
    led.setLED(4);
    delay(500);
    led.setLED(8);
    delay(500);
    led.setLED(4);
    delay(500);
    led.setLED(8);
    delay(500);
    led.setLED(WAIT);
    delay(500);
}
/**************************************************************************************************/
//Initiliazize bay with current configuration
void CommDirector::initConfig(int activeSlots, int config1, int config2, int config3){

    transmit(); //Transmit configuration to Pi
}
/**************************************************************************************************/
