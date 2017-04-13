#include <Arduino.h>
#include <CommDirector.h>
#include <MasterController.h>
#include <Timer.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x3F // Define I2C Address where the SainSmart LCD is
const unsigned long PERIOD1 = 1000;    //one second
const unsigned long PERIOD2 = 2000;    //one second

//LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
LiquidCrystal_I2C lcd(I2C_ADDR,2,1,0,4,5,6,7);

#define ECHO_DELAY 100
CommDirector commDirector = CommDirector(1);
int  i = 0;
int  k = 0;
char temp[20];
Timer t1;
Timer t2;
void subTransmitTest();
void replyTest();
void relayTest();
void echoTest();
void progress();

void setup() {
  commDirector.reply.masterState = 0x11;
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

  commDirector.command.subCommand[0].setDataPacket(0x00 , 0x00 );
  t1.every(PERIOD1, relayTest);
  t2.every(PERIOD2, echoTest);
  lcd.print("Waiting.");
}

void loop() {
  t1.update();
  t2.update();
}

void relayTest(){
  if(commDirector.recieve()){
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Command Data In");
      lcd.setCursor(0, 1);
      sprintf(temp,"control:%i sc1:%i %i",  commDirector.command.masterControl,
                                        commDirector.command.subCommand[0].dataPacket[0],
                                        commDirector.command.subCommand[0].dataPacket[1]);
      lcd.print(temp);
      delay(ECHO_DELAY);
      subTransmitTest();
  }
}
void echoTest(){
  if(commDirector.subRecieve(1)){
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SubReply Recieved.");
    sprintf(temp,"status:%i command:%i", commDirector.reply.subReply[0].dataPacket[0],
                                         commDirector.reply.subReply[0].dataPacket[1]);
    lcd.setCursor(0, 1);
    lcd.print(temp);
    delay(ECHO_DELAY);
    replyTest();
    //Serial.print("Recieved: "); Serial.print(commDirector.reply.subReply[0].dataPacket[0]);
    //Serial.print(" "); Serial.println(commDirector.reply.subReply[0].dataPacket[1]);
  }
}

void subTransmitTest(){
  //commDirector.command.subCommand[0].setDataPacket('A' , k);
  lcd.setCursor(0, 2);
  lcd.print("SubCommand Data Out");
  sprintf(temp,"conifg:%i command:%i", commDirector.command.subCommand[0].dataPacket[0],
                                       commDirector.command.subCommand[0].dataPacket[1]);
  lcd.setCursor(0, 3);
  lcd.print(temp);
  if(!commDirector.subTransmit(1)) lcd.print("Error");
}

void replyTest(){
  lcd.setCursor(0, 2);
  lcd.print("Reply Data Echoed");
  sprintf(temp,"State:%i sr1:%i %i", commDirector.reply.masterState,
                                    commDirector.reply.subReply[0].dataPacket[0],
                                    commDirector.reply.subReply[0].dataPacket[1]);
  lcd.setCursor(0, 3);
  lcd.print(temp);
  if(!commDirector.transmit()) lcd.print("Error");
}

void progress(){
  //lcd.setCursor(i,0);
  if(i < 20) {
    //lcd.print(".");
     i++;
  }else  {
    // lcd.clear();
     i = 0;}
}
