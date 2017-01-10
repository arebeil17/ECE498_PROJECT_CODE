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
bool CommDirector::recieve(){
  int size = Serial.available();
  unsigned char buffer[size];

    if(size >= 3){ //Check if serial data available
       led.setLED(RECIEVE);
      //Serial.readBytes(buf, len)
       Serial.readBytes(buffer, size);
       command.dataPacket[0] = buffer[0];
       command.dataPacket[1] = buffer[1];
       command.dataPacket[2] = buffer[2];
       command.setCommandData();
       delay(50);
       return true;
    }
    return false;
}
/**************************************************************************************************/
void CommDirector::transmit(){
    led.setLED(SEND);
    //Serial.write(buf, len)
    reply.setDataPacket();
    if(!Serial.write(reply.dataPacket, 2)){
      led.setLED(7); //Orange status for not data sent
    }
    Serial.flush();
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
void CommDirector::initConfig(int activeSlots, int config1, int config2, int config3){
    startUp();
    reply.setDataPacket(0x00 , (activeSlots & 0xC0)| (config1 & 0x30) |
                               (config1 & 0x0C)    | (config1 & 0x03));
    transmit(); //Transmit configuration to Pi
}
/**************************************************************************************************/
