/*
* File: Identify.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 3rd, 2016
*
* Description: Implementation of Identify class's interface.
*
*/
/**************************************************************************************************/
#include "Identify.h"
/**************************************************************************************************/

Identify::Identify(){
    for (int i = 0; i < SLOT_COUNT; i++) {
       slotId[i] = NO_MODULE;
       //Setup pins and designated ports for identifying payloads
       port[0 + 3*i] = ROOT_PIN + 2*i + 6*(i);       pinMode(port[0 + 3*i], INPUT);
       port[1 + 3*i] = ROOT_PIN + 2*(i + 1) + 6*(i); pinMode(port[1 + 3*i], INPUT);
       port[2 + 3*i] = ROOT_PIN + 2*(i + 2) + 6*(i); pinMode(port[2 + 3*i], INPUT);
    }

}
/**************************************************************************************************/
bool Identify::readPorts(){
  int scanResult[3] = {0,0,0};
  int idCnt = 0;
  for (int i = 0; i < SLOT_COUNT; i++) {
      if(digitalRead(port[0 + 3*i])) scanResult[0] = 1; else scanResult[0] = 0;
      if(digitalRead(port[1 + 3*i])) scanResult[1] = 1; else scanResult[1] = 0;
      if(digitalRead(port[2 + 3*i])) scanResult[2] = 1; else scanResult[2] = 0;

      slotId[i] = 1*scanResult[0] + 2*scanResult[1] + 4*scanResult[2];
      if(slotId[i] != NO_MODULE) idCnt++;
  }
  if(idCnt > 0) return true;
  return false;
}
/**************************************************************************************************/
int Identify::getSlotId(int slot){

    if(slot <= SLOT_COUNT && slot > 0)
      return slotId[slot - 1];
    else
      return 0;
}
/**************************************************************************************************/
String Identify::getModuleName(int slot){
    if(slot >= SLOT_COUNT && slot > 0){
        if(slotId[slot - 1] == LED_MODULE) return "LED Module";
        else if(slotId[slot - 1]  == SOUND_MODULE) return "SOUND Module";
        else if(slotId[slot - 1]  == LCD_MODULE) return "LCD Module";
        else if(slotId[slot - 1]  == NO_MODULE) return "No Module";
        else return "Unknown Module";
    }else{
      return "Error";
    }
}
