#include <Arduino.h>
#include <Command.h>
#include <Payload.h>
#include <Reply.h>
#include <led.h>


const int SEND = 2,
          RECIEVE = 3,
          WAIT = 5,
          NO_COMM = 1;

int i = 6, j = 0;

boolean transmit = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);

  //Init LED pins
  pinMode(R_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
}

void loop() {

    if(j < 200 && !transmit){
      setLED(SEND);
      delay(200);
      Serial.print("Hello Pi!\n");
      transmit = true;
    }else{
      setLED(WAIT);
    }

   if (Serial.available()) {
       //Convert data recieved from char to number
       i = Serial.read() - '0';
       if(j >= 200) j = 0;

       setLED(RECIEVE);
       delay(200);
       setLED(i);
       delay(500);
       transmit = false;
   }else if(j >= 200){
        setLED(NO_COMM);
        delay(100);
   }else {
        j++;
   }
   delay(100);
}
