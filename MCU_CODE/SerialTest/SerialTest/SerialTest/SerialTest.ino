#include <Arduino.h>
#include <led.h>
#include <CommDirector.h>

CommDirector commDirector;
bool transmit = false;
int t = 0;
#define TIMEOUT 2000

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  commDirector.initConfig(3,1,1,1);
  commDirector.reply.setDataPacket('A','A');
}

void loop(){
  if(!transmit){
    t++;
    if( t == TIMEOUT) {
      commDirector.transmit();
      delay(100);
    }else if(t > TIMEOUT){
      commDirector.led.setLED(NO_COMM);
      commDirector.transmit();
      delay(1000);
    }
  }else{
    t = 0;
    transmit = false;
  }
  delay(5);
}

void serialEvent() {
  //Check if data was recieved and store it
  if(commDirector.recieve()){
    //Since data was recieved reply with confirmation
    commDirector.transmit();
    delay(50);
    transmit = true;
    commDirector.led.setLED(WAIT);
  }
}
//
// void loop() {
//
//     if(j < 200 && !transmit){
//       led.setLED(SEND);
//       delay(200);
//       Serial.print("Hello Pi!\n");
//       transmit = true;
//     }else{
//       led.setLED(WAIT);
//     }
//
//    if (Serial.available()) {
//        //Convert data recieved from char to number
//        i = Serial.read() - '0';
//        if(j >= 200) j = 0;
//
//        led.setLED(RECIEVE);
//        delay(200);
//        led.setLED(i);
//        delay(500);
//        transmit = false;
//    }else if(j >= 200){
//         led.setLED(NO_COMM);
//         delay(100);
//    }else {
//         j++;
//    }
//    delay(100);
// }
