/*
* File: MasterController.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 3rd, 2017
*
* Description: Implementation of Module class's interface.
*
*/
/**************************************************************************************************/
#include "MasterController.h"
/**************************************************************************************************/

MasterController::MasterController()
{
    activeCount = 0;
    active_Slot1 = false;
    active_Slot2 = false;
    active_Slot3 = false;
    commandReceived = false;
    echoReady   =  false;
    state = INITIAL;
    stateResolved = false;

}
/**************************************************************************************************/
void MasterController::identify_Routine(uint8_t calls){
      uint8_t slotCnt = 0;
      commDirector.subTransmit(1);
      commDirector.subTransmit(2);
      commDirector.subTransmit(3);
      delay(10);
      if(commDirector.subReceive(1)) {
        slotCnt++; active_Slot1 = true;
      }
      if(commDirector.subReceive(2)) {
        slotCnt++; active_Slot2 = true;
      }
      if(commDirector.subReceive(3)) {
        slotCnt++; active_Slot3 = true;
      }
      //All payloads identified or identification time exceeded
      if(slotCnt == 3 || calls >= 50){
          stateResolved = true;
          activeCount = slotCnt;
      }
      //State is resolved transmit bay status to command
      if(stateResolved){
          commDirector.reply.masterState = ((WAIT & 0x0F) << 4) | (active_Slot3 << 2) | (active_Slot2 << 1) | (active_Slot1);
          commDirector.reply.updateDataPacket(); //update reply data before sending
          commDirector.transmit();  //transmit prepared packet
          state = WAIT;
      }
}
/**************************************************************************************************/
void MasterController::wait_Routine(){
    //check if command Received from user
    if(commDirector.receive()){
       state = RELAY;
       commDirector.reply.masterState = ((RELAY & 0x0F) << 4)| (active_Slot3 << 2) | (active_Slot2 << 1) | (active_Slot1);
       commandReceived = true;
       stateResolved = true;
     }
}
/**************************************************************************************************/
void MasterController::relay_Routine(){
    if(commDirector.subTransmitAll(active_Slot1, active_Slot2, active_Slot3) == activeCount){
      state = ECHO;
      commDirector.reply.masterState = ((ECHO & 0x0F) << 4)| (active_Slot3 << 2) | (active_Slot2 << 1) | (active_Slot1);
    }else{
      state = REPLY;
      commDirector.reply.masterState = ((REPLY & 0x0F) << 4)| (active_Slot3 << 2) | (active_Slot2 << 1) | (active_Slot1);
    }
    stateResolved = true;
}
/**************************************************************************************************/
void MasterController::echo_Routine(uint8_t calls){
    if(calls >= 10 || commDirector.subReceiveAll(active_Slot1, active_Slot2, active_Slot3)){
        state = REPLY;
        commDirector.reply.masterState = ((REPLY & 0x0F) << 4)| (active_Slot3 << 2) | (active_Slot2 << 1) | (active_Slot1);
        stateResolved = true;
    }
}
/**************************************************************************************************/
void MasterController::reply_Routine(){
    if(commDirector.transmit()){
      state = WAIT;
      commDirector.reply.masterState = ((WAIT & 0x0F) << 4)  | (active_Slot3 << 2) | (active_Slot2 << 1) | (active_Slot1);
      stateResolved = true;
    }
}
