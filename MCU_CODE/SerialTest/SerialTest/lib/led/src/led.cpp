
#include "led.h"

Led::Led(){
  //Init LED pins
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
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
      analogWrite(R_LED, HIGH);
      analogWrite(G_LED, HIGH);
      analogWrite(B_LED, HIGH);
   break;
  }
}
