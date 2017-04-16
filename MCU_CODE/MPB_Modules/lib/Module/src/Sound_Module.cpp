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
    beepCount = 0;
    volumeCount = 0;
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
    {   case NO_COMMAND:
            maxSteps = standard;
            beepBurst(step, 3, 100, 35);
        break;
        case SIMULT_FUNCTION_1: maxSteps = standard;
            beepBurst(step, 1, 100, 35);
        break;
        case SIMULT_FUNCTION_2: maxSteps = standard;
            beepBurst(step, 2, 100, 35);
        break;
        case SIMULT_FUNCTION_3: maxSteps = standard;
            beepBurst(step, 3, 100, 35);
        break;
        case SIMULT_FUNCTION_4: maxSteps = standard;
            beepBurst(step, 4, 100, 35);
        break;
        case SIMULT_FUNCTION_5: maxSteps = standard;
            beepBurst(step, 5, 100, 35);
        break;
        case SIMULT_FUNCTION_6: maxSteps = standard;
            beepBurst(step, 6, 100, 35);
        break;
        case SIMULT_FUNCTION_7: maxSteps = 25000;
            digitalWrite(TRACK0_PIN, HIGH);
            digitalWrite(TRACK1_PIN, LOW);
            digitalWrite(TRACK2_PIN, HIGH);
        break;
        default: return true;
    }
    if(command != lastCommand && command != NO_COMMAND){
        digitalWrite(TRACK0_PIN, HIGH);
        digitalWrite(TRACK1_PIN, HIGH);
        digitalWrite(TRACK2_PIN, HIGH);
    }

    if((step >= maxSteps)){
        beepCount = 0;
        volumeCount = 0;
        digitalWrite(TRACK0_PIN, HIGH);
        digitalWrite(TRACK1_PIN, HIGH);
        digitalWrite(TRACK2_PIN, HIGH);
        digitalWrite(VOL_DOWN_PIN, HIGH);
        digitalWrite(VOL_UP_PIN, HIGH);
        return true;
    }
    lastCommand = command;
    return false;
}
/**************************************************************************************************/
bool Sound_Module::independentFunction(uint16_t command, uint16_t step){
    switch(command)
    {   case NO_COMMAND:
              maxSteps = standard;
              beepBurst(step, 3, 100, 35);
        break;
        case INDEPENDENT_FUNCTION_1: maxSteps = 25000;
            digitalWrite(TRACK0_PIN, HIGH);
            digitalWrite(TRACK1_PIN, LOW);
            digitalWrite(TRACK2_PIN, HIGH);
        break;
        case INDEPENDENT_FUNCTION_2: maxSteps = 23500;
            digitalWrite(TRACK0_PIN, HIGH);
            digitalWrite(TRACK1_PIN, HIGH);
            digitalWrite(TRACK2_PIN, LOW);
        break;
        case INDEPENDENT_FUNCTION_3: maxSteps = 1000;
            volumeControl(step, 100, 50, 10, true);
            beepBurst(step, 10, 100, 35);
        break;
        case INDEPENDENT_FUNCTION_4: maxSteps = 1000;
            volumeControl(step, 100, 50, 10, false);
            beepBurst(step, 10, 100, 35);
        break;
        case INDEPENDENT_FUNCTION_5: maxSteps = 1000 + 175;
            sequentialBeep(step, 500, 175);
        break;
        case INDEPENDENT_FUNCTION_6: maxSteps = 1000 + 210;
            sequentialBeep(step, 500, 210);
        break;
        default: return true;
    }
    if(command != lastCommand && command != NO_COMMAND){
        digitalWrite(TRACK0_PIN, HIGH);
        digitalWrite(TRACK1_PIN, HIGH);
        digitalWrite(TRACK2_PIN, HIGH);
    }

    if((step >= maxSteps)){
        beepCount = 0;
        volumeCount = 0;
        digitalWrite(TRACK0_PIN, HIGH);
        digitalWrite(TRACK1_PIN, HIGH);
        digitalWrite(TRACK2_PIN, HIGH);
        digitalWrite(VOL_DOWN_PIN, HIGH);
        digitalWrite(VOL_UP_PIN, HIGH);
        return true;
    }
    lastCommand = command;
    return false;
}
/**************************************************************************************************/
void Sound_Module::sequentialBeep(uint16_t step, uint16_t every, uint16_t endStep){
      if(step%every == 0){
            //Serial.print("Beep, step: "); Serial.println(step);
            digitalWrite(TRACK0_PIN, LOW);
            this->endStep = step + endStep;
            //Serial.print("Endstep: "); Serial.println(endStep);
      }else if(this->endStep == step){
              digitalWrite(TRACK0_PIN, HIGH);
      }
}
/**************************************************************************************************/
void Sound_Module::beepBurst(uint16_t step, uint8_t numBeeps, uint16_t every, uint16_t endStep){
        if((step%every == 0) && beepCount < numBeeps){
              beepCount++;
              //Serial.print("Beep, step: "); Serial.println(step);
              digitalWrite(TRACK0_PIN, LOW);
              this->endStep = step + endStep;
              //Serial.print("Endstep: "); Serial.println(endStep);
        }else if(this->endStep == step){
                digitalWrite(TRACK0_PIN, HIGH);
        }

}
/**************************************************************************************************/
void Sound_Module::volumeControl(uint16_t step, uint16_t every, uint16_t endStep, uint8_t volDiff, bool increase){
      if((step%every == 0) && volumeCount < volDiff){
            volumeCount++;
            if(increase){
              digitalWrite(VOL_DOWN_PIN, HIGH);
              digitalWrite(VOL_UP_PIN, LOW);
            }else{
              digitalWrite(VOL_DOWN_PIN, LOW);
              digitalWrite(VOL_UP_PIN, HIGH);
            }
            vol_endStep = step + endStep;
            //Serial.print("Endstep: "); Serial.println(endStep);
      }else if(vol_endStep == step){
          digitalWrite(VOL_DOWN_PIN, HIGH);
          digitalWrite(VOL_UP_PIN, HIGH);
      }
}
/**************************************************************************************************/
void Sound_Module::reset(){
    beepCount = 0;
    vol_endStep = 0;
    volumeCount = 0;
    digitalWrite(TRACK0_PIN, HIGH);
    digitalWrite(TRACK1_PIN, HIGH);
    digitalWrite(TRACK2_PIN, HIGH);
}
