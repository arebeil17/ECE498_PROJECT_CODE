#include <Arduino.h>
#include <CommDirector.h>
#include <MasterController.h>
#include <Timer.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x3F // Define I2C Address where the SainSmart LCD is
const unsigned long ID_PERIOD = 100;    //ms
const unsigned long WAIT_PERIOD = 10;   //ms
const unsigned long RELAY_PERIOD = 10;  //ms
const unsigned long ECHO_PERIOD = 10;  //ms
const unsigned long REPLY_PERIOD= 10;   //ms
#define DEBUG_DELAY 500
#define DEBUG true

//LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
LiquidCrystal_I2C lcd(I2C_ADDR,2,1,0,4,5,6,7);

#define ECHO_DELAY 100
MasterController controller;
int  i = 0;
int  k = 0;
char temp[20];
Timer t1;
Timer t2;
Timer t3;
Timer t4;
Timer t5;
uint8_t calls = 0;

void identifyUpdate();
void waitUpdate();
void relayUpdate();
void echoUpdate();
void replyUpdate();

void setup() {

  Serial.begin(38400);
  // put your setup code here, to run once:
  lcd.begin(20, 4);
  // Switch on the backlight
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();
  lcd.setCursor ( 0, 0 );
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();

  t1.every(ID_PERIOD, identifyUpdate);
  t2.every(WAIT_PERIOD, waitUpdate);
  t3.every(RELAY_PERIOD, relayUpdate);
  t4.every(ECHO_PERIOD, echoUpdate);
  t5.every(REPLY_PERIOD, replyUpdate);
  lcd.print("Waiting.");
}

void loop() {
  switch(controller.state)
  {   case INITIAL:
            controller.state = IDENTIFY;
            delay(50);
      break;
      case IDENTIFY:
            t1.update();
      break;
      case WAIT:
            t2.update();
      break;
      case RELAY:
            t3.update();
      break;
      case ECHO:
            t4.update();
      break;
      case REPLY:
            t5.update();
      break;
  }
}
void identifyUpdate(){
    lcd.clear(); lcd.setCursor ( 0, 0 ); lcd.print("IDENTIFY");
    calls++;
    sprintf(temp,"Calls: %i",  calls);
    lcd.setCursor ( 0, 1 ); lcd.print(temp);
    //-------------------------------------------------------------
    controller.identify_Routine(calls);
    if(controller.stateResolved){
      calls = 0; controller.stateResolved = false;
      if(DEBUG) delay(DEBUG_DELAY);
    }
}
void waitUpdate(){
    if(1000%calls == 0){
    lcd.clear(); lcd.setCursor ( 0, 0 ); lcd.print("WAIT");}
    calls++;
    sprintf(temp,"Calls: %i Active: %i",  calls, controller.activeCount);
    lcd.setCursor ( 0, 1 ); lcd.print(temp);
    //-------------------------------------------------------------
    controller.wait_Routine();
    if(controller.stateResolved){
      calls = 0; controller.stateResolved = false;
      if(DEBUG) delay(DEBUG_DELAY);
    }
}
void relayUpdate(){
   lcd.clear(); lcd.setCursor ( 0, 0 ); lcd.print("RELAY");
   calls++;
   sprintf(temp,"Calls: %i",  calls);
   lcd.setCursor ( 0, 1 ); lcd.print(temp);
   //-------------------------------------------------------------
    controller.relay_Routine();
    if(controller.stateResolved){
      calls = 0; controller.stateResolved = false;
      if(DEBUG) delay(DEBUG_DELAY);
    }
}
void echoUpdate(){
    lcd.clear(); lcd.setCursor ( 0, 0 ); lcd.print("ECHO");
    calls++;
    sprintf(temp,"Calls: %i",  calls);
    lcd.setCursor ( 0, 1 ); lcd.print(temp);
    //-------------------------------------------------------------
    controller.echo_Routine(calls);
    if(controller.stateResolved){
      calls = 0; controller.stateResolved = false;
      if(DEBUG) delay(DEBUG_DELAY);
    }
}
void replyUpdate(){
    lcd.clear(); lcd.setCursor ( 0, 0 ); lcd.print("REPLY");
    calls++;
    sprintf(temp,"Calls: %i",  calls);
    lcd.setCursor ( 0, 1 ); lcd.print(temp);
    //-------------------------------------------------------------
    controller.reply_Routine();
    if(controller.stateResolved){
      calls = 0; controller.stateResolved = false;
      if(DEBUG) delay(DEBUG_DELAY);
    }
}
