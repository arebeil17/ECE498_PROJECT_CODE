#include <Arduino.h>
#include <CommDirector.h>
#include <LCD.h>
#include <Wire.h>
#include <LiquidCrystal.h>
#include <Timer.h>

#define REDLITE 9
#define GREENLITE 10
#define BLUELITE 11

const unsigned long PERIOD1 = 250;
const unsigned long PERIOD2 = 10;
// initialize the library with the numbers of the interface pins
//RS EN DB4 DB5 DB6 DB7
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
// you can change the overall brightness by range 0 -> 255
int brightness = 255;

void setBacklight(uint8_t r, uint8_t g, uint8_t b);
void rainbow();
void recieveTest();
void echo();

int i = 0;
char buffer[2];
char temp[20];
Timer t1;
Timer t2;
Timer t3;

CommDirector commDirector;

void setup() {
    lcd.begin(20, 4);
    pinMode(REDLITE, OUTPUT);
    pinMode(GREENLITE, OUTPUT);
    pinMode(BLUELITE, OUTPUT);
    brightness = 255;
    lcd.print("Ready!");
    delay(1000);
    lcd.setCursor(0 , 1);
    //lcd.print("Data recieved.");
    t1.every(PERIOD1, recieveTest);
    t2.every(PERIOD2, rainbow);
}
void loop() {
    t1.update();
    t2.update();
}
void setBacklight(uint8_t r, uint8_t g, uint8_t b) {
    // normalize the red LED - its brighter than the rest!
    r = map(r, 0, 255, 0, 100);
    g = map(g, 0, 255, 0, 150);
    r = map(r, 0, 255, 0, brightness);
    g = map(g, 0, 255, 0, brightness);
    b = map(b, 0, 255, 0, brightness);
    // common anode so invert!
    r = map(r, 0, 255, 255, 0);
    g = map(g, 0, 255, 255, 0);
    b = map(b, 0, 255, 255, 0);
    //Serial.print("R = "); Serial.print(r, DEC);
    //Serial.print("G = "); Serial.print(g, DEC);
    //Serial.print("B = "); Serial.println(b, DEC);
    analogWrite(REDLITE, r);
    analogWrite(GREENLITE, g);
    analogWrite(BLUELITE, b);
}
void recieveTest(){
  lcd.setCursor(0, 0);
  if(commDirector.recieve()){
    lcd.clear();
    lcd.print("Receiving");
    sprintf(temp,"config:%i command:%i", commDirector.command.dataPacket[0],
                                         commDirector.command.dataPacket[1]);
    lcd.setCursor(0, 1);
    lcd.print(temp);
    //Echo back to master with command confirmation
    echo();
  }
}
void echo(){
  lcd.setCursor(0, 2);
  lcd.print("Transmitting");
  commDirector.reply.setReplyData(commDirector.command.dataPacket[0], commDirector.command.dataPacket[1]);
  sprintf(temp,"status:%i command:%i", commDirector.reply.dataPacket[0],
                                        commDirector.reply.dataPacket[1]);
  lcd.setCursor(0, 3);
  lcd.print(temp);
  commDirector.transmit();
}
void rainbow(){
    if(i <= 255) setBacklight(i, 0, 255-i);
    else if(i <= 510) setBacklight(255-i + 255, i - 255, 0);
    else if(i > 510) setBacklight(0, 255-i + 510, i -510);

    if(i < 765) i++;
    else i = 0;
}
