/*
* File: Sound_Module.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 10th, 2017
*
* Description: Implementation of Sound_Module class's interface.
*
*/
/**************************************************************************************************/
#include "Sound_Module.h"
/**************************************************************************************************/

Sound_Module::Sound_Module()
{
    moduleType = SOUND_MODULE;
    standard = 3000;
    maxSteps = 1000;
}
/**************************************************************************************************/
void Sound_Module::initSound(){
  pinMode(TRACK0_PIN, OUTPUT); digitalWrite(TRACK0_PIN, HIGH);
  pinMode(TRACK1_PIN, OUTPUT); digitalWrite(TRACK1_PIN, HIGH);
  pinMode(TRACK2_PIN, OUTPUT); digitalWrite(TRACK2_PIN, HIGH);
  pinMode(VOL_DOWN_PIN, OUTPUT); digitalWrite(VOL_DOWN_PIN, HIGH);
  pinMode(VOL_UP_PIN , OUTPUT); digitalWrite(VOL_UP_PIN, HIGH);
  //digitalWrite(pin, value)
}
/**************************************************************************************************/
bool Sound_Module::simultaneousFunction(uint16_t command, uint16_t step){
    switch(command)
    {   case NO_COMMAND: maxSteps = standard + 35;
              sequentialBeep(step, 1500, 35);
        break;
        case SIMULT_FUNCTION_1: maxSteps = 25000;
            digitalWrite(TRACK0_PIN, HIGH);
            digitalWrite(TRACK1_PIN, LOW);
            digitalWrite(TRACK2_PIN, HIGH);
        break;
        case SIMULT_FUNCTION_2: maxSteps = 23500;
            digitalWrite(TRACK0_PIN, HIGH);
            digitalWrite(TRACK1_PIN, HIGH);
            digitalWrite(TRACK2_PIN, LOW);
        break;
        case SIMULT_FUNCTION_3: maxSteps = 1000 + 105;
            sequentialBeep(step, 500, 105);
        break;
        case SIMULT_FUNCTION_4: maxSteps = 1000 + 140;
            sequentialBeep(step, 500, 140);
        break;
        case SIMULT_FUNCTION_5: maxSteps = 1000 + 175;
            sequentialBeep(step, 500, 175);
        break;
        case SIMULT_FUNCTION_6: maxSteps = 1000;
            sequentialBeep(step, 500, 210);
        break;
        default: return true;
    }
    if(command != lastCommand && command != NO_COMMAND){
      digitalWrite(TRACK0_PIN, HIGH);
      digitalWrite(TRACK1_PIN, HIGH);
      digitalWrite(TRACK2_PIN, HIGH);
    }
    lastCommand = command;
    if(step >= maxSteps){
      digitalWrite(TRACK0_PIN, HIGH);
      digitalWrite(TRACK1_PIN, HIGH);
      digitalWrite(TRACK2_PIN, HIGH);
      return true;
    }
    else return false;
}
/**************************************************************************************************/
void Sound_Module::sequentialBeep(uint16_t step, uint16_t every, uint16_t endStep){
      if(step%every == 0){
          Serial.print("Beep, step: "); Serial.println(step);
          digitalWrite(TRACK0_PIN, LOW);
          this->endStep = step + endStep;
          Serial.print("Endstep: "); Serial.println(endStep);
      }else if(this->endStep == step){
          digitalWrite(TRACK0_PIN, HIGH);
      }
}
void Sound_Module::reset(){
    digitalWrite(TRACK0_PIN, HIGH);
    digitalWrite(TRACK1_PIN, HIGH);
    digitalWrite(TRACK2_PIN, HIGH);
}
