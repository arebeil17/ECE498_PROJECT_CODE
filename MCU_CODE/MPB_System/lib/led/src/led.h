#ifndef LED_H
#define LED_H

#include <Arduino.h>

#define  SEND  2
#define  RECEIVE  3
//#define  WAIT  5
#define  NO_COMM  1

class Led {
  private:
    int R_LED;
    int G_LED;
    int B_LED;

  public:
    //Default pins are 7,8,9 PWM
    Led();

    //Specify the PWM pin numbers for the RGB LED
    Led(int R_LED, int G_LED, int B_LED);

    void setLED(int mode);
};



#endif // LED_H
