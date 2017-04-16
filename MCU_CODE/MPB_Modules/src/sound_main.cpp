#include <Arduino.h>
#include <Controller.h>
#include <CommDirector.h>
//#include <LCD.h>
#include <Wire.h>
//#include <LiquidCrystal.h>
#include <Timer.h>
#include "Adafruit_TPA2016.h"

const unsigned long PERIOD1 = 10;
const unsigned long PERIOD2 = 10;
const unsigned long WAIT_PERIOD = 10;   //ms
const unsigned long EXECUTE_PERIOD = 10;   //ms
#define DEBUG_DELAY 500
#define DEBUG false

void receive();
void echo();
void waitUpdate();
void executeUpdate();

Adafruit_TPA2016 audioamp = Adafruit_TPA2016();

int i = 0;
char buffer[2];
char temp[20];
Timer receiveTimer;
Timer t1;
Timer t2;
uint8_t command = 0;
uint16_t step = 0;
uint8_t lastState = WAIT;

Controller controller = Controller(SOUND_MODULE);

void setup() {
    Serial.begin(38400);
    //Serial.println("TPA2016 Audio Test");
    audioamp.begin();
    audioamp.setGain(10);
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
    step++;
    if(step%100 == 0){ Serial.println("WAIT");
                        Serial.println(controller.sound_Module.beepCount);}
    controller.wait_Routine(step);
    if(controller.stateResolved){ step = 0; controller.stateResolved = false;
    if(DEBUG) delay(DEBUG_DELAY);}

}
void executeUpdate(){
    step++;
    if(step%100 == 0){ Serial.println("EXECUTE");
                        Serial.println(controller.sound_Module.beepCount);}
    controller.execute_Routine(step);
    if(controller.stateResolved){ step = 0; controller.stateResolved = false;
    if(DEBUG) delay(DEBUG_DELAY);}

}
void receive(){
    controller.receive_Routine();
    if(controller.stateResolved){ step = 0; controller.stateResolved = false;}
}
