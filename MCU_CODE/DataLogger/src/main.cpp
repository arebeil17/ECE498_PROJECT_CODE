#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include <Timer.h>

// A simple data logger for the Arduino analog pins
#define redLED 3
#define greenLED 2
// how many milliseconds between grabbing data and logging it. 1000 ms is once a second
#define LOG_INTERVAL  1 // mills between entries (reduce to take more/faster data)
const unsigned long PERIOD1 = 1;    //one second
const unsigned long PERIOD2 = 50;    //one second
Timer t1;
Timer t2;
// how many milliseconds before writing the logged data permanently to disk
// set it to the LOG_INTERVAL to write each time (safest)
// set it to 10*LOG_INTERVAL to write all data every 10 datareads, you could lose up to
// the last 10 reads if power is lost but it uses less power and is much faster!
#define SYNC_INTERVAL 1000 // mills between calls to flush() - to write data to the card
uint32_t syncTime = 0; // time of last sync()

#define ECHO_TO_SERIAL   0// echo data to serial port
#define WAIT_TO_START    0 // Wait for serial input in setup()

Adafruit_LIS3DH lis = Adafruit_LIS3DH();
//lis.read();      // get X Y and Z data at once
/* Or....get a new sensor event, normalized */
sensors_event_t event;

#if defined(ARDUINO_ARCH_SAMD)
// for Zero, output on USB Serial console, remove line below if using programming port to program the Zero!
   #define Serial SerialUSB
#endif

RTC_DS1307 RTC; // define the Real Time Clock object

// for the data logging shield, we use digital pin 10 for the SD cs line
const int chipSelect = 10;

// the logging file
File logfile;

bool toggle = false;
bool pressed= false;

void logData();
void input();

void error(char *str)
{
  Serial.print("error: ");
  Serial.println(str);

  while(1);
}

void setup(void)
{
  pinMode(7, INPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);

  #ifndef ESP8266
    while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
  #endif

    Serial.begin(38400);
    Serial.println("LIS3DH test!");

    if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
      Serial.println("Couldnt start");
      while (1);
    }
    Serial.println("LIS3DH found!");

    lis.setRange(LIS3DH_RANGE_16_G);   // 2, 4, 8 or 16 G!

    Serial.print("Range = "); Serial.print(2 << lis.getRange());
    Serial.println("G");
    delay(5000);

  Serial.println();

#if WAIT_TO_START
  Serial.println("Type any character to start");
  while (!Serial.available());
#endif //WAIT_TO_START

  // initialize the SD card
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to
  // output, even if you don't use it:
  pinMode(10, OUTPUT);

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    error("Card failed, or not present");
  }
  Serial.println("card initialized.");

  // create a new file
  char filename[] = "LOGGER00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE);
      break;  // leave the loop!
    }
  }

  if (! logfile) {
    error("couldnt create file");
  }

  Serial.print("Logging to: ");
  Serial.println(filename);

  // connect to RTC
  Wire.begin();
  if (!RTC.begin()) {
    logfile.println("RTC failed");
#if ECHO_TO_SERIAL
    Serial.println("RTC failed");
#endif  //ECHO_TO_SERIAL
  }


  logfile.println("millis,accel_X,accel_Y,accel_Z");
#if ECHO_TO_SERIAL
  Serial.println("millis,accel_X,accel_Y,accel_Z");
#endif //ECHO_TO_SERIAL
delay(1000);
  // If you want to set the aref to something other than 5v
  analogReference(EXTERNAL);

  t1.every(PERIOD1, logData);
  t2.every(PERIOD2, input);
}

void loop(void)
{
  t1.update();
  t2.update();
}

void input(){
  if(digitalRead(7)) {
    pressed = true;
    Serial.println("Button Pressed");
  }else if(!digitalRead(7)) {
    if(pressed){
      toggle = !toggle;
      Serial.println("Button Toggled");
      if(toggle){
       Serial.println("Logging Data.");
       digitalWrite(greenLED, HIGH);
       digitalWrite(redLED, LOW);
     }
    }
    pressed = false;
  }
}

void logData()
{
  if(toggle){
      lis.getEvent(&event);
      // Then print out the raw data
      /* Display the results (acceleration is measured in m/s^2) */
    //  Serial.print("\t\tX: "); Serial.print(event.acceleration.x);
    //  Serial.print(" \tY: "); Serial.print(event.acceleration.y);
    //  Serial.print(" \tZ: "); Serial.print(event.acceleration.z);
    //  Serial.println(" m/s^2 ");

      //DateTime now;

      // delay for the amount of time we want between readings
      //delay((LOG_INTERVAL -1) - (millis() % LOG_INTERVAL));
      //delay(LOG_INTERVAL);
      // log milliseconds since starting
      uint32_t m = millis();
      logfile.print(m);           // milliseconds since start
      logfile.print(", ");
    #if ECHO_TO_SERIAL
      Serial.print(m);         // milliseconds since start
      Serial.print(", ");
    #endif
      //logfile.print(event.acceleration.x);
      //logfile.print(", ");
      //logfile.print(event.acceleration.y);
      //logfile.print(", ");
      logfile.print(event.acceleration.z);
      logfile.print(", ");
    #if ECHO_TO_SERIAL
      //Serial.print(event.acceleration.x);
      //Serial.print(", ");
      //Serial.print(event.acceleration.y);
      //Serial.print(", ");
      Serial.print(event.acceleration.z);
      Serial.print(", ");
    #endif //ECHO_TO_SERIAL


      logfile.println();
    #if ECHO_TO_SERIAL
      Serial.println();
    #endif // ECHO_TO_SERIAL

      // Now we write data to disk! Don't sync too often - requires 2048 bytes of I/O to SD card
      // which uses a bunch of power and takes time
      if ((millis() - syncTime) < SYNC_INTERVAL) return;
      syncTime = millis();

      logfile.flush();
  }else{
    Serial.println("Stopped Logging Data.");
    delay(250);
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
  }
}
