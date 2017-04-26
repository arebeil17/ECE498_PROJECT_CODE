/*
* File: LED_Module.cpp
* Author: Andres Rebeil
* NetID: andres07
* Date: January 10th, 2017
*
* Description: Implementation of LED_Module class's interface.
*
*/
/**************************************************************************************************/
#include "LED_Module.h"
/**************************************************************************************************/

LED_Module::LED_Module()
{
    moduleType = LED_MODULE;
    standard = 3000;
    maxSteps = 1000;
    brightness = 0;
    ascend = true;
    brightness = 0;
    hold_on = false;
    flashStep = 0;
    flashCount = 0;
    clusterSize = 5; //clusterSize = 37;
    fadeFactor = 50; //fadeFactor = 7;
    twinkleCount = 0;
    strobeCount = 0;
    select = 0;
}
/**************************************************************************************************/
//Initialize module as an LED Payload specify slot position
bool LED_Module::initStrip(Adafruit_NeoPixel* strip){
      //strip = Adafruit_NeoPixel(NUM_PIXELS, LED_STRIP_PIN, NEO_RGBW  + NEO_KHZ800);
      strip->begin();
      strip->show(); // Initialize all pixels to 'off'
      sweepColor = strip->Color(0, 255, 0, 0);
      baseColor = strip->Color(0, 0, 0, 0);
      colorWipe(baseColor, true, strip);
      return true;
}
/**************************************************************************************************/
bool LED_Module::simultaneousFunction(uint16_t command, uint16_t step, Adafruit_NeoPixel* strip){
    switch(command)
    {   case NO_COMMAND: maxSteps = standard;
             breatheColor = strip2.Color(0, 0, brightness, 0);
             breathe(step, false, 5,  255, 1, strip);
        break;
        case SIMULT_FUNCTION_1: maxSteps = standard;
            flashColor = getColorCode(RED);
            flash(step, 1, 10, strip);
        break;
        case SIMULT_FUNCTION_2: maxSteps = standard;
            flashColor = getColorCode(GREEN);
            flash(step, 2, 10, strip);
        break;
        case SIMULT_FUNCTION_3: maxSteps = standard;
            flashColor = getColorCode(BLUE);
            flash(step, 3, 10, strip);
        break;
        case SIMULT_FUNCTION_4: maxSteps = standard;
            flashColor = getColorCode(WHITE);
            flash(step, 4, 10, strip);
        break;
        case SIMULT_FUNCTION_5: maxSteps = standard;
            flashColor = getColorCode(PURPLE);
            flash(step, 5, 10, strip);
        break;
        case SIMULT_FUNCTION_6: maxSteps = standard;
            flashColor = getColorCode(CORAL);
            flash(step, 6, 10, strip);
        break;
        case SIMULT_FUNCTION_7: maxSteps = standard;
            if(step%3 == 0){
              clusterSize = 8; fadeFactor = 30;
              baseColor = strip->Color(0, 0, 0, 0);
              if(WheelPos >= 255) WheelPos = 0;
              WheelPos = round(step/(standard*1.0) * 255);
              sweepColor = Wheel(WheelPos, strip);
              Sweep(sweepColor, strip);
            }
        break;
        default: return true;
    }
    if(step >= maxSteps){
       baseColor = strip->Color(0, 0, 0, 0);
       ascend = true;
       brightness = 0;
       hold_on = false;
       flashStep = 0;
       flashCount = 0;
       twinkleCount = 0;
       strobeCount = 0;
       return true;
    }else return false;
}
/**************************************************************************************************/
bool LED_Module::independentFunction(uint16_t command, uint16_t step, Adafruit_NeoPixel* strip){
    switch(command)
    {   case NO_COMMAND: maxSteps = standard;
             breatheColor = strip2.Color(0, 0, brightness, 0);
             breathe(step, false, 5,  255, 0, strip);
        break;
        case INDEPENDENT_FUNCTION_1: maxSteps = standard;
            if(WheelPos >= 255) WheelPos = 0;
            waitFunction(step, strip);
        break;
        case INDEPENDENT_FUNCTION_2: maxSteps = 25000;
            if(step%3 == 0){
            clusterSize = 8; fadeFactor = 30;
            baseColor = strip->Color(0, 0, 0, 0);
            sweepColor = getColorCode(RED);
            NightRider(strip);}
        break;
        case INDEPENDENT_FUNCTION_3: maxSteps = 23500;
            if(step%3 == 0){
              clusterSize = 8; fadeFactor = 30;
              baseColor = strip->Color(0, 0, 0, 0);
              if(WheelPos >= 255) WheelPos = 0;
              WheelPos = round(step/(standard*1.0) * 255);
              sweepColor = Wheel(WheelPos, strip);
              Sweep(sweepColor, strip);
           }
        break;
        case INDEPENDENT_FUNCTION_4: maxSteps = standard;
            randomTwinkle(step, 50, NUM_PIXELS, strip);
        break;
        case INDEPENDENT_FUNCTION_5: maxSteps = standard;
            sparkle(strip2.Color(20,20,20,0),
               strip2.Color(255,255,255,100),
               step, 25, strip);
        break;
        case INDEPENDENT_FUNCTION_6: maxSteps = standard;
            if(step%3 == 0){
            sweepColor = getColorCode(PURPLE);
            Sweep(sweepColor, strip);}
        break;
        case INDEPENDENT_FUNCTION_7: maxSteps = standard;
            if(step%3 == 0){
            sweepColor = getColorCode(CORAL);
            Sweep(sweepColor, strip);}
        break;
        default: return true;
    }
    if(step >= maxSteps){
       baseColor = getColorCode(0);
       ascend = true;
       brightness = 0;
       hold_on = false;
       flashStep = 0;
       flashCount = 0;
       colorWipe(getColorCode(0), true, strip);
       strobeCount = 0;
       return true;
    }else return false;
}
/**************************************************************************************************/
void LED_Module::breathe(uint16_t step, bool hold, uint8_t low, uint8_t high, uint8_t duration_factor, Adafruit_NeoPixel* strip){
      if(step <= 1){
          if((low < 0) | (low > 255) | (low > high)) low = LOW_LEVEL;
          if((high < 0) | (high > 255) | (low > high)) high = HIGH_LEVEL;
          switchCount = 0;
      }
      if(ascend){
          if(switchCount >= duration_factor){
             brightness++;
             switchCount = 0;
          }
          switchCount++;
          if(brightness >= (high - 1)) ascend = false;
      }else{
          if(switchCount >= duration_factor){
             brightness--;
             switchCount = 0;
          }
          switchCount++;
          if(brightness <= (low + 1)) ascend = true;
      }
      if(hold){
          if(brightness == (high - 1) && (holdCount < 25)){
            brightness = high;
            holdCount++;
          }else{
            holdCount = 0;
          }
      }
      //Display current breathe level color
      colorWipe(breatheColor, true, strip);
}
/**************************************************************************************************/
void LED_Module::flash(uint16_t step, uint8_t numFlashes, uint8_t rate, Adafruit_NeoPixel* strip){
    uint8_t flashInterval = maxSteps/rate;

    if(flashStep < (flashInterval/2)){
        flashStep++;
    }else{
        flashStep = 0;
        hold_on = !hold_on;
        if(hold_on){
          flashCount++;
        }
    }

    if(hold_on && (flashCount <= numFlashes)) colorWipe(flashColor, true, strip);
    else colorWipe(getColorCode(0), true, strip);
}
/**************************************************************************************************/
void LED_Module::waitFunction(uint16_t step, Adafruit_NeoPixel* strip){
    //Serial.println(round(step/(standard*1.0) * 255));
    //Serial.println(round(step/(standard*1.0) * 255));
    WheelPos = round(step/(standard*1.0) * 255);
    colorWipe(Wheel(WheelPos, strip), true, strip);
    //colorWipe(strip->Color(64, 255, 64, 0), true, strip);
}
/**************************************************************************************************/
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t LED_Module::Wheel(byte WheelPos, Adafruit_NeoPixel* strip) {
      WheelPos = 255 - WheelPos;
      if(WheelPos < 85) {
        return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
      }
      if(WheelPos < 170) {
        WheelPos -= 85;
        return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
      }
      WheelPos -= 170;
      return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
/**************************************************************************************************/
// Fill the dots one after the other with a color
void LED_Module::colorWipe(uint32_t c, bool show, Adafruit_NeoPixel* strip) {
    for(uint16_t i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, c);
    }
    if(show) strip->show();
}
/***********************************************************************************``***************/
void LED_Module::NightRider(Adafruit_NeoPixel* strip){
    if((ledPos < strip->numPixels() - 1) && forward){
        ledPos++; moveCluster(ledPos, true, strip, true);
        //if((strip.numPixels() - clusterSize) == ledPos)
        if((strip->numPixels() - 1) == ledPos)
          forward = false;
    }else if(ledPos > 0 && !forward){
        ledPos--; moveCluster(ledPos, false, strip, true);
        if(!ledPos) {
          ledPos = 0; forward = true;
        }
    }
}
/**************************************************************************************************/
void LED_Module::Sweep(uint32_t c, Adafruit_NeoPixel* strip){
    if((ledPos < strip->numPixels() - 1) && forward){
        ledPos++; moveCluster(ledPos, true, strip, false);
        if((strip->numPixels() - 1) == ledPos)
          forward = false;
    }else if(ledPos > 0 && !forward){
        ledPos--; moveCluster(ledPos, false, strip, false);
        if(!ledPos) {
          ledPos = 0; forward = true;
        }
    }
}
/**************************************************************************************************/
void LED_Module::moveCluster(int start, bool direction, Adafruit_NeoPixel* strip, bool nightRider) {
    colorWipe(baseColor, true, strip);
    //strip->setPixelColor(start, sweepColor);
    for(uint16_t i = 0; i < clusterSize; i++) {
        if(direction){
          // strip.setPixelColor(start + i, strip.Color(0, 255 - fadeFactor*i, 0, 0));
           if(nightRider ) strip->setPixelColor(start - i, strip->Color(0, 255 - fadeFactor*i, 0, 0));
           else strip->setPixelColor(start - i, sweepColor);
        }else{
        //  strip.setPixelColor((clusterSize - 1) + start - i, strip.Color(0, 255 - fadeFactor*i, 0, 0)));
           if(nightRider) strip->setPixelColor(start + i, strip->Color(0, 255 - fadeFactor*i, 0, 0));
           else strip->setPixelColor(start + i, sweepColor);
        }
    }
    strip->show();
}
/**************************************************************************************************/
void LED_Module::randomTwinkle(uint16_t step, uint16_t every, uint16_t max, Adafruit_NeoPixel* strip){
    if(step <= 1)  colorWipe(getColorCode(0), true, strip);
    if(step%every == 0){
       twinkleCount++;
       strip->setPixelColor(random(strip->numPixels()),strip2.Color(random(255), random(255), random(255), random(25)));
       strip->show();
    }else if(twinkleCount > max){
       colorWipe(getColorCode(0), true, strip);
       twinkleCount = 0;
    }
}
/**************************************************************************************************/
void LED_Module::sparkle(uint32_t c, uint32_t s, uint16_t step, uint16_t every, Adafruit_NeoPixel* strip){
   if(step%every == 0){
        select = random(NUM_PIXELS);
        colorWipe(c,true, strip);
        //strip->setPixelColor(select,strip2.Color(150,150,255,0));
        strip->setPixelColor(select, s);
        strip->show();
    }else if(step%(every/5) == 0){
      strip->setPixelColor(select,c);
      strip->show();
    }
}
/**************************************************************************************************/
uint32_t LED_Module::getColorCode(uint8_t color){
    switch (color) {
      case RED: return strip2.Color(0, 255, 0, 0);
      case GREEN: return strip2.Color(255, 0, 0, 0);
      case BLUE: return strip2.Color(0, 0, 255, 0);
      case WHITE: return strip2.Color(0, 0, 0, 255);
      case PURPLE: return strip2.Color(0, 255, 255, 0);
      case CORAL: return strip2.Color(64, 255, 64, 0);
      case LT_BLUE: return strip2.Color(0, 0, 255, 50);
      default: return strip2.Color(0, 0, 0, 0);
    }
}
/**************************************************************************************************/
void LED_Module::reset(){
    ascend = true;
    brightness = 0;
    hold_on = false;
    flashStep = 0;
    flashCount = 0;
    twinkleCount = 0;
    strobeCount = 0;
}
