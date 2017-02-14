#include <Arduino.h>
#include <CommDirector.h>
#include <ModuleController.h>
#include <Timer.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x3F // Define I2C Address where the SainSmart LCD is
const unsigned long PERIOD1 = 250;    //one second
//const unsigned long PERIOD2 = 1000;    //one second

//LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
LiquidCrystal_I2C lcd(I2C_ADDR,2,1,0,4,5,6,7);

CommDirector commDirector = CommDirector(1);
int  i = 0;
int  k = 0;
char temp[20];
Timer t1;
Timer t2;
void commTest();
void progress();

void setup() {
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

  commDirector.subCommand[0].updateDataPacket(0x00 , 0x00 );
  t1.every(PERIOD1, commTest);
  t2.every(PERIOD1, progress);
}

void loop() {
  t1.update();
  t2.update();
  k = i;
}

void commTest(){
  lcd.setCursor(0, 1);
  lcd.print("Transmitting ");
  commDirector.subCommand[0].updateDataPacket(0x01 , k);
  sprintf(temp,"control:%i command:%i", commDirector.subCommand[0].dataPacket[0],
                                        commDirector.subCommand[0].dataPacket[1]);
  lcd.setCursor(0, 2);
  lcd.print(temp);
  if(!commDirector.subTransmit(1)) lcd.print("Error");
}

void progress(){
  lcd.setCursor(i,0);
  if(i < 20) { lcd.print("."); i++;
  }else  { lcd.clear(); i = 0;}
}
