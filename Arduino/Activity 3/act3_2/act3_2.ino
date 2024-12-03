#include <PRIZM.h>
PRIZM prizm;

float botWidth = 10.2; 
float botLength = 13.0;

void setup() {
  // initialize PRIZM
  prizm.PrizmBegin();
  prizm.setServoSpeed(1, 50);    
}

void loop() {
  prizm.setServoPosition(1, 180);
  delay(2000);
  signalLeft();
  signalRight();
  prizm.PrizmEnd();
}

void signalRight() {
  prizm.setServoPosition(1, 90);
  for(int j = 0; j < 3; j++ ) {
    prizm.setRedLED(1);
    delay(500);
    prizm.setRedLED(0);
    delay(500);
  }
  delay(1000);
  prizm.setServoPosition(1, 180);
  delay(2000);
}

void signalLeft() {
  prizm.setServoPosition(1, 0);
  for(int j = 0; j < 3; j++ ) {
    prizm.setGreenLED(1);
    delay(500);
    prizm.setGreenLED(0);
    delay(500);
  }
  delay(1000);
  prizm.setServoPosition(1, 180);
  delay(2000);
}
