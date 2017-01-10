/*
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include <Arduino.h>
#include <CommDirector.h>
#include <led.h>
#include <ModuleController.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x3F // Define I2C Address where the SainSmart LCD is
#define BACKLIGHT_PIN 3
#define LIMIT 8


//LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
LiquidCrystal_I2C lcd(I2C_ADDR,2,1,0,4,5,6,7);

Identify id;

int temp = 0;

void setup()
{
  id.readPorts();
  temp = id.getSlotId(1);
  // put your setup code here, to run once:
  lcd.begin (20, 4);
  // Switch on the backlight
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.home();
}

void loop()
{
  id.readPorts();
    if(temp != id.getSlotId(1)){
      temp = id.getSlotId(1);
      lcd.clear();
      lcd.setCursor ( 0, 0 );
      lcd.print("slotID: ");
      lcd.print(id.getSlotId(1));
      lcd.setCursor ( 0, 1 );
      lcd.print(id.getModuleName(1));
      lcd.setCursor ( 0, 2 );
      lcd.print("Ports used: ");
      lcd.print(NUM_MODULES);
      lcd.setCursor ( 0, 3 );
      lcd.print("Ports:");
      lcd.print(" "); lcd.print(id.port[0]);
      lcd.print(" "); lcd.print(id.port[1]);
      lcd.print(" "); lcd.print(id.port[2]);
      delay(50);
  }
  delay(5);
}
