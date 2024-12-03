#include <PRIZM.h>
PRIZM prizm;

// LISTED AS EXERCISE 3 IN LOGBOOK

void setup() {
  // initialize PRIZM
  prizm.PrizmBegin();    
}

void loop() {
  // Run when green button is clicked
  while(prizm.readStartButton() == 1) {
    //Create a counter
    int i = 0;
    // S, repeat 3x short flashes
    while(i < 3) {
      prizm.setRedLED(1);
      delay(250);
      prizm.setRedLED(0);
      delay(250);
      i++;
    }
    i = 0;
    // O, repeat 3x long flashes
    while(i < 3) {
      prizm.setRedLED(1);
      delay(500);
      prizm.setRedLED(0);
      delay(500);
      i++;
    }
    i = 0;
    // S, repeat 3x short flashes
    while(i < 3) {
      i++;
      prizm.setRedLED(1);
      delay(250);
      prizm.setRedLED(0);
      delay(250);
    }
  }
}