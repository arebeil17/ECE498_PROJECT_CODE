#ifndef SOUND_MODULE_H
#define SOUND_MODULE_H
/*************/
/*
* File: Sound_Module.h
* Author: Andres Rebeil
* NetID: andres07
* Date: January 10th, 2017
*
* Description: This header file contains the Sound_Module class's interface.
*/

/**************************************************************************************************/
//#include <Module.h>
#include <Arduino.h>
#include <Wire.h>
#include <Keywords.h>
/**************************************************************************************************/

using namespace std;

#define TRACK0_PIN 2
#define TRACK1_PIN 3
#define TRACK2_PIN 4

#define VOL_UP_PIN 9
#define VOL_DOWN_PIN 8

//Sound_Module is a Subclass of the Module Superclass
class Sound_Module {
    private:
      uint8_t lastCommand;
    public:
      uint8_t moduleType;
      uint16_t standard;
      uint16_t maxSteps;
      uint16_t endStep;
      uint16_t vol_endStep;
      uint16_t beepCount;
      //volume control
      uint8_t volumeCount;

      Sound_Module();

      void initSound();

      bool simultaneousFunction(uint16_t command, uint16_t step);
      bool independentFunction(uint16_t command, uint16_t step);

      void sequentialBeep(uint16_t step, uint16_t every, uint16_t endStep);
      void beepBurst(uint16_t step, uint8_t numBeeps, uint16_t every, uint16_t endStep);
      void volumeControl(uint16_t step, uint16_t every, uint16_t endStep, uint8_t volDiff, bool increase);

      void reset();
};

#endif // SOUND_MODULE_H
