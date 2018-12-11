#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

//350-400 seems a good limit of dry. 1024 = dry, 1 = wet.

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Started.");
pinMode(A0,INPUT);

  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz
  
  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(150);
 // myMotor->run(FORWARD);
  // turn on motor
 // myMotor->run(RELEASE);
}

void loop() {
  delay(10000);
  uint8_t i;
  int soil_n = analogRead(A0);
    if (soil_n>350) {
       for (i=0; i<30; i++) {
            myMotor->run(FORWARD);
            int soil_n = analogRead(A0);
            if (soil_n<350) {
              myMotor->run(RELEASE);
              break;
            }
            delay (1000);
       }
       myMotor->run(RELEASE); 
    }
   delay(300000);
}
