#include <PRIZM.h>
PRIZM prizm;

float botWidth = 10.2; 
float botLength = 13.0;

void setup() {
  // initialize PRIZM
  prizm.PrizmBegin();    
}

void loop() {
  signalLeft();
  signalRight();
  prizm.PrizmEnd();
}

void signalRight() {
  for(int j = 0; j < 3; j++ ) {
    prizm.setRedLED(1);
    delay(500);
    prizm.setRedLED(0);
    delay(500);
  }
}

void signalLeft() {
  for(int j = 0; j < 3; j++ ) {
    prizm.setGreenLED(1);
    delay(500);
    prizm.setGreenLED(0);
    delay(500);
  }
}
