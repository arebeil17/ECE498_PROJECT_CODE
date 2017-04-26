#ifndef LED_MODULE_H
#define LED_MODULE_H
/*************/
/*
* File: LED_Module.h
* Author: Andres Rebeil
* NetID: andres07
* Date: January 10th, 2017
*
* Description: This header file contains the LED_Module class's interface.
*/

/**************************************************************************************************/
#include <Module.h>
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Keywords.h>
/**************************************************************************************************/

using namespace std;

#define LED_STRIP_PIN 22
#define NUM_PIXELS 20
#define LOW_LEVEL 52
#define HIGH_LEVEL 255

//LED_Module is a Subclass of the Module Superclass
class LED_Module{
    private:
      bool forward = true;
      unsigned int clusterSize = 37;
      unsigned int fadeFactor = 7;
      int cycle2 = 255;
      int cycle1 = 1;
      unsigned int ledPos = 0;
      uint8_t WheelPos = 0;
      uint8_t colorSelect = 0;
      uint8_t strobeCount;
      uint8_t select;
    public:
      //For breathe control
      uint8_t brightness;
      uint32_t breatheColor;
      uint16_t delta;
      bool ascend;
      uint16_t switchCount;
      uint16_t holdCount;
      uint8_t twinkleCount;
      //For flash control
      bool hold_on;
      uint16_t flashStep;
      uint16_t flashCount;
      uint32_t flashColor;
      //For sweep control
      uint32_t sweepColor;
      uint32_t baseColor;
      uint8_t moduleType;
      uint16_t standard;
      uint16_t maxSteps;
      Adafruit_NeoPixel strip2;

      LED_Module();

      bool initStrip(Adafruit_NeoPixel* strip);

      bool simultaneousFunction(uint16_t command, uint16_t step, Adafruit_NeoPixel* strip);
      bool independentFunction(uint16_t command, uint16_t step, Adafruit_NeoPixel* strip);

      void breathe(uint16_t step, bool hold, uint8_t low, uint8_t high, uint8_t duration_factor
                  , Adafruit_NeoPixel* strip);
      void flash(uint16_t step, uint8_t numFlashes, uint8_t rate, Adafruit_NeoPixel* strip);
      void waitFunction(uint16_t step, Adafruit_NeoPixel* strip);
      uint32_t Wheel(byte WheelPos, Adafruit_NeoPixel* strip);
      void colorWipe(uint32_t c, bool show, Adafruit_NeoPixel* strip);
      void NightRider(Adafruit_NeoPixel* strip);
      void Sweep(uint32_t c, Adafruit_NeoPixel* strip);
      void moveCluster(int start, bool direction, Adafruit_NeoPixel* strip, bool nightRider);
      void LED_Module::randomTwinkle(uint16_t step, uint16_t every, uint16_t max, Adafruit_NeoPixel* strip);
      void sparkle(uint32_t c, uint32_t s, uint16_t step, uint16_t every, Adafruit_NeoPixel* strip);
      uint32_t getColorCode(uint8_t color);
      void reset();
};

#endif // LED_MODULE_H
