#ifndef LED_H
#define LED_H

#include <Arduino.h>

#define R_LED 9
#define G_LED 11
#define B_LED 13

#define  SEND  2
#define  RECIEVE  3
#define  WAIT  5
#define  NO_COMM  1

class Led {

  public:

    Led();

    void setLED(int mode);
};



#endif // LED_H
