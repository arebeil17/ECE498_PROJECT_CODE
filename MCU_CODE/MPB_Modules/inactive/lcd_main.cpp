#include <Arduino.h>
#include <Controller.h>
#include <CommDirector.h>
#include <LCD.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Timer.h>

#define REDLITE 9
#define GREENLITE 10
#define BLUELITE 11

const unsigned long PERIOD1 = 10;
const unsigned long PERIOD2 = 10;
const unsigned long WAIT_PERIOD = 10;   //ms
const unsigned long EXECUTE_PERIOD = 10;   //ms
#define DEBUG_DELAY 500
#define DEBUG false
// initialize the library with the numbers of the interface pins
//RS EN DB4 DB5 DB6 DB7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
// you can change the overall brightness by range 0 -> 255
int brightness = 255;

//void setBacklight(uint8_t r, uint8_t g, uint8_t b);
//void rainbow();
void receive();
void echo();
void waitUpdate();
void executeUpdate();


int i = 0;
char buffer[2];
char temp[20];
Timer receiveTimer;
Timer t1;
Timer t2;
uint8_t command = 0;
uint16_t step = 0;
uint8_t lastState = WAIT;

Controller controller = Controller(LCD_MODULE);

void setup() {
    lcd.begin(20, 4);
    receiveTimer.every(PERIOD1, receive);
    t1.every(WAIT_PERIOD, waitUpdate);
    t2.every(EXECUTE_PERIOD, executeUpdate);
}
void loop() {
    receiveTimer.update();
    switch(controller.state){
        case INITIAL:
            controller.state = WAIT;
        break;
        case WAIT:
            t1.update();
        break;
        case EXECUTE:
            t2.update();
        break;
    }
}

void waitUpdate(){
    lcd.clear(); lcd.setCursor ( 0, 0 ); lcd.print("WAIT");
    sprintf(temp,"step: %i",  step);
    lcd.setCursor ( 0, 1 ); lcd.print(temp);
    //-------------------------------------------------------------
    step++;
    controller.wait_Routine(step);
    if(controller.stateResolved){ step = 0; controller.stateResolved = false;
    if(DEBUG) delay(DEBUG_DELAY);}

}
void executeUpdate(){
    lcd.clear(); lcd.setCursor ( 0, 0 ); lcd.print("EXECUTE");
    sprintf(temp,"cmd:%i step:%i", controller.currentCommand,  step);
    lcd.setCursor ( 0, 1 ); lcd.print(temp);
  //-------------------------------------------------------------
    step++;
    controller.execute_Routine(step);
    if(controller.stateResolved){ step = 0; controller.stateResolved = false;
    if(DEBUG) delay(DEBUG_DELAY);}

}
void receive(){
    controller.receive_Routine();
    if(controller.stateResolved){ step = 0; controller.stateResolved = false;}
}

// void setBacklight(uint8_t r, uint8_t g, uint8_t b) {
//     // normalize the red LED - its brighter than the rest!
//     r = map(r, 0, 255, 0, 100);
//     g = map(g, 0, 255, 0, 150);
//     r = map(r, 0, 255, 0, brightness);
//     g = map(g, 0, 255, 0, brightness);
//     b = map(b, 0, 255, 0, brightness);
//     // common anode so invert!
//     r = map(r, 0, 255, 255, 0);
//     g = map(g, 0, 255, 255, 0);
//     b = map(b, 0, 255, 255, 0);
//     //Serial.print("R = "); Serial.print(r, DEC);
//     //Serial.print("G = "); Serial.print(g, DEC);
//     //Serial.print("B = "); Serial.println(b, DEC);
//     analogWrite(REDLITE, r);
//     analogWrite(GREENLITE, g);
//     analogWrite(BLUELITE, b);
// }
// void rainbow(){
//     if(i <= 255) setBacklight(i, 0, 255-i);
//     else if(i <= 510) setBacklight(255-i + 255, i - 255, 0);
//     else if(i > 510) setBacklight(0, 255-i + 510, i -510);
//
//     if(i < 765) i++;
//     else i = 0;
// }
