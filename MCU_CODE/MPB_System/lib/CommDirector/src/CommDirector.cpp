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
    Serial3.begin(38400);
    Serial2.begin(38400);
    Serial1.begin(38400);
}
/**************************************************************************************************/
CommDirector::CommDirector(int activeSlots){
    Serial.begin(38400);
    if(activeSlots >= 3) Serial3.begin(38400);
    if(activeSlots >= 2) Serial2.begin(38400);
    if(activeSlots >= 1) Serial1.begin(38400);
}
/**************************************************************************************************/
bool CommDirector::receive(){
  int size = Serial.available();
  unsigned char buffer[size];

    if(size >= 8){ //Check if serial data available
       led.setLED(RECEIVE);
      //Serial.readBytes(buf, len)
       Serial.readBytes(buffer, size);
       //check that the data packet begins with the correct start byte
       if(buffer[0] != START_BYTE) return false;
       //shift buffer left to remove start byte
       for(int i=0; i < 8; i++) buffer[i] = buffer[i + 1];
       command.setDataPacket(buffer);
       //delay(50);
       return true;
    }
    return false;
}
/**************************************************************************************************/
//Transmit bay and payload status to Pi
bool CommDirector::transmit(){
    led.setLED(SEND);
    //Serial.write(buf, len)
    reply.updateDataPacket();
    if(!Serial.write(reply.dataPacket, 8)){
      led.setLED(7); //Orange status for no data sent
      return false;
    }
    Serial.flush();
    return true;
}
/**************************************************************************************************/
//Receive data from specified payload slot
bool CommDirector::subReceive(int slot){
    int size = 0;
    unsigned char buffer[64];
    switch(slot){
      case 1:
        size = Serial1.available();
        if(size >= 3) Serial1.readBytes(buffer, size);
        else return false;
        break;
      case 2:
        size = Serial2.available();
        if(size >= 3) Serial2.readBytes(buffer, size);
        else return false;
        break;
      case 3:
        size = Serial3.available();
        if(size >= 3) Serial3.readBytes(buffer, size);
        else return false;
        break;
      default:
        return false;
    }
    //Serial.print("Buffer: "); Serial.print(buffer[0]);
    //Serial.print(" "); Serial.print(buffer[1]);
    //Serial.print(" "); Serial.println(buffer[2]);
    if(buffer[0] != START_BYTE) return false;
    reply.subReply[slot - 1].setReplyData(buffer[1], buffer[2]);
    return true;
}
/**************************************************************************************************/
//Transmit currently stored command to specified payload/module slot
bool CommDirector::subTransmit(int slot){
    unsigned char buffer[3];
    buffer[0] = START_BYTE;
    buffer[1] = command.subCommand[slot - 1].dataPacket[0];
    buffer[2] = command.subCommand[slot - 1].dataPacket[1];
    switch(slot){
      case 1:
        if(!Serial1.write(buffer, 3)) return false;
        return true;
      case 2:
        if(!Serial2.write(buffer, 3)) return false;
        return true;
      case 3:
        if(!Serial3.write(buffer, 3)) return false;
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
//Transmit to all enabled/selected submodules
int CommDirector::subTransmitAll(bool slot1, bool slot2, bool slot3){
    int transmitCnt = 0;
    //transmit only to active slots
    if(slot1){
      //Transmit to submodule only if enabled
      if(command.slotEnable[0]) subTransmit(1);
      transmitCnt++;
    }
    if(slot2){
      //Transmit to submodule only if enabled
      if(command.slotEnable[1]) subTransmit(2);
      transmitCnt++;
    }
    if(slot3){
      //Transmit to submodule only if enabled
      if(command.slotEnable[2]) subTransmit(3);
      transmitCnt++;
    }
    return transmitCnt;
}
/**************************************************************************************************/
//Receive data from all active submodules
bool CommDirector::subReceiveAll(bool slot1, bool slot2, bool slot3){
    uint8_t receiveCnt = 0;
    uint8_t active = (slot1) + (slot2) + (slot3);
    //transmit only to active slots
    if(slot1){ subReceive(1); receiveCnt++;}
    if(slot2){ subReceive(2); receiveCnt++;}
    if(slot3){ subReceive(3); receiveCnt++;}

    if(receiveCnt >= active) return true;
    return false;
}
