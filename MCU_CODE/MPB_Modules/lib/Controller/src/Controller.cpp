/*
* File: Controller.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: March 16th, 2017
*
* Description: Implementation of Module class's interface.
*
*/
/**************************************************************************************************/
#include "Controller.h"
/**************************************************************************************************/

Controller::Controller(){
    state = INITIAL;
    maxSteps = 255;
    stateResolved = false;
    currentCommand = NO_COMMAND;
}
/**************************************************************************************************/
Controller::Controller(uint8_t moduleType){
      state = INITIAL;
      stateResolved = false;
      currentCommand = NO_COMMAND;
      init(moduleType);
}
/**************************************************************************************************/
Controller::Controller(uint8_t moduleType, Adafruit_NeoPixel* strip){
      state = INITIAL;
      stateResolved = false;
      currentCommand = NO_COMMAND;
      init(moduleType);
      led_Module.initStrip(strip);
}
/**************************************************************************************************/
void Controller::init(uint8_t moduleType){
    switch(moduleType){
  			case LED_MODULE:
            this->moduleType = moduleType;
            maxSteps = led_Module.standard;
  			break;
        case LCD_MODULE:
            this->moduleType = moduleType;
            maxSteps = display_Module.standard;
            display_Module.initDisplay();
  			break;
  			case SOUND_MODULE:
            this->moduleType = moduleType;
            maxSteps = sound_Module.standard;
            sound_Module.initSound();
  			break;
        default:
            this->moduleType = NO_MODULE;
        break;
	}
}
/**************************************************************************************************/
void Controller::wait_Routine(uint16_t step){
    if(commandExecution(moduleType, NO_COMMAND, step, NULL)){
        done();
    }
}
/**************************************************************************************************/
void Controller::wait_Routine(uint16_t step, Adafruit_NeoPixel* strip){
    if(commandExecution(moduleType, NO_COMMAND, step, strip)){
        done();
    }
}
/**************************************************************************************************/
void Controller::execute_Routine(uint16_t step){
    if(commandExecution(moduleType, currentCommand, step, NULL)){
        done();
    }
}
void Controller::execute_Routine(uint16_t step, Adafruit_NeoPixel* strip){
    if(commandExecution(moduleType, currentCommand, step, strip)){
        done();
    }
}
/**************************************************************************************************/
void Controller::receive_Routine(){
    if(commDirector.receive()){
        if(commDirector.command.abort){
            done();
            commDirector.transmit();
        }else if(commDirector.command.command ==  NO_COMMAND){
              currentCommand = commDirector.command.command;
              state = state;
        }else if(validCommandCheck(commDirector.command.command)){
            currentCommand = commDirector.command.command;
            state = EXECUTE;
            stateResolved = true;
        }
        commDirector.stageTransmit(state, moduleType, currentCommand);
        commDirector.transmit();
    }

}
/**************************************************************************************************/
void Controller::done(){
    resetMaxStep(moduleType);
    state = WAIT;
    currentCommand = NO_COMMAND;
    commDirector.stageTransmit(state, moduleType, currentCommand);
    commDirector.command.clear();
    stateResolved = true;
    if(moduleType == SOUND_MODULE) sound_Module.reset();
    //commDirector.transmit();
}
/**************************************************************************************************/
bool Controller::commandExecution(uint8_t moduleType, uint8_t command, uint16_t step, Adafruit_NeoPixel* strip){
      switch (moduleType) {
        case LED_MODULE:
            if(command < 128) {
              if(led_Module.simultaneousFunction(command, step, strip)) return true;
            }
            return false;
        break;
        case LCD_MODULE:
            if(command < 128){
               if(display_Module.simultaneousFunction(command, step)) return true;
             }
             return false;
        break;
        case SOUND_MODULE:
            if(command < 128){
               if(sound_Module.simultaneousFunction(command, step)) return true;
             }
             return false;
        break;
        default: return true;
      }
}
/**************************************************************************************************/
bool Controller::validCommandCheck(uint8_t command){
      switch(command)
      {   case NO_COMMAND:  return true;
          case SIMULT_FUNCTION_1:  return true;
          case SIMULT_FUNCTION_2:  return true;
          case SIMULT_FUNCTION_3:  return true;
          case SIMULT_FUNCTION_4:  return true;
          case SIMULT_FUNCTION_5:  return true;
          case SIMULT_FUNCTION_6:  return true;
          case INDEPENDENT_FUNCTION_1: ; return true;
          case INDEPENDENT_FUNCTION_2:  return true;
          case INDEPENDENT_FUNCTION_3:  return true;
          case INDEPENDENT_FUNCTION_4:  return true;
          case INDEPENDENT_FUNCTION_5:  return true;
          case INDEPENDENT_FUNCTION_6:  return true;
          default: return false;
      }
}
/**************************************************************************************************/
void Controller::resetMaxStep(uint8_t moduleType){
    switch (moduleType) {
      case NO_MODULE:    maxSteps = 255; break;
      case LED_MODULE:   maxSteps = led_Module.standard; break;
      case LCD_MODULE:   maxSteps = display_Module.standard; break;
      case SOUND_MODULE: maxSteps = sound_Module.standard;; break;
    }
}
