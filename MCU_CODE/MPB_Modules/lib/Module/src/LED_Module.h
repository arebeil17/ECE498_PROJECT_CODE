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
/**************************************************************************************************/

using namespace std;

//LED_Module is a Subclass of the Module Superclass
class LED_Module: public Module {
    private:

    public:
      Adafruit_NeoPixel strip;

      LED_Module();

      bool initStrip(unsigned int slot);
};

#endif // LED_MODULE_H
