
#include "led.h"

Led::Led(){
  this->R_LED = 7;
  this->G_LED = 8;
  this->B_LED = 9;
  //Init LED pins
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);

  setLED(0);
}

//Specify the pin numbers for the RGB LED
Led::Led(int R_LED, int G_LED, int B_LED){
    this->R_LED = R_LED;
    this->G_LED = G_LED;
    this->B_LED = B_LED;
    //Init LED pins
    pinMode(R_LED, OUTPUT);
    pinMode(G_LED, OUTPUT);
    pinMode(B_LED, OUTPUT);

    setLED(0);
}

void Led::setLED(int mode)
{
  switch(mode){
     //RED
    case 1:
      analogWrite(R_LED, 0);
      analogWrite(G_LED, 255);
      analogWrite(B_LED, 255);
    break;
    //GREEN
    case 2:
      analogWrite(R_LED, 255);
      analogWrite(G_LED, 0);
      analogWrite(B_LED, 255);
     break;
    //BLUE
    case 3:
      analogWrite(R_LED, 255);
      analogWrite(G_LED, 255);
      analogWrite(B_LED, 0);
     break;
    //PURPLE
    case 4:
      analogWrite(R_LED, 192);
      analogWrite(G_LED, 255);
      analogWrite(B_LED, 0);
     break;
    //TEAL
    case 5:
      analogWrite(R_LED, 255);
      analogWrite(G_LED, 45);
      analogWrite(B_LED, 0);
     break;
    //PINK
    case 6:
      analogWrite(R_LED, 0);
      analogWrite(G_LED, 192);
      analogWrite(B_LED, 192);
     break;
    //ORANGE
    case 7:
      analogWrite(R_LED, 0);
      analogWrite(G_LED, 192);
      analogWrite(B_LED, 255);
     break;
    //WHITE
   case 8:
      analogWrite(R_LED, 0);
      analogWrite(G_LED, 0);
      analogWrite(B_LED, 0);
     break;
    //OFF
   default:
      analogWrite(R_LED, 255);
      analogWrite(G_LED, 255);
      analogWrite(B_LED, 255);
   break;
  }
}
