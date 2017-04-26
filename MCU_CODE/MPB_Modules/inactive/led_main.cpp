#include <Arduino.h>
#include <Controller.h>
#include <CommDirector.h>
#include <LCD.h>
#include <Wire.h>
#include <Timer.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 22

Adafruit_NeoPixel strip;

const unsigned long PERIOD1 = 10;
const unsigned long PERIOD2 = 10;
const unsigned long WAIT_PERIOD = 10;   //ms
const unsigned long EXECUTE_PERIOD = 10;   //ms
#define DEBUG_DELAY 500
#define DEBUG false

int brightness = 255;

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

Controller controller;

void setup() {
    Serial.begin(38400);
    //Serial.println("Starting");
    strip = Adafruit_NeoPixel(NUM_PIXELS, PIN, NEO_RGBW  + NEO_KHZ800);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
    controller = Controller(LED_MODULE);
    //Serial.println("Initialization Complete.");
    //controller.led_Module.colorWipe(strip.Color(0, 255, 0, 0), true);
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
    //if(step%100 == 0) {Serial.print("Wait "); Serial.println(step);}
    controller.wait_Routine(step, &strip);
    if(controller.stateResolved){ step = 0; controller.stateResolved = false;
    if(DEBUG) delay(DEBUG_DELAY);}
}
void executeUpdate(){
    step++;
    //if(step%100 == 0) Serial.println("Execute");
    controller.execute_Routine(step, &strip);
    if(controller.stateResolved){ step = 0; controller.stateResolved = false;
    if(DEBUG) delay(DEBUG_DELAY);}

}
void receive(){
    if(controller.receive_Routine())
      controller.led_Module.colorWipe(strip.Color(0,0,0,0), true, &strip);
    if(controller.stateResolved){ step = 0; controller.stateResolved = false;}
}
