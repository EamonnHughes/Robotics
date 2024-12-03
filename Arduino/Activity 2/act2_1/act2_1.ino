#include <PRIZM.h>
PRIZM prizm;

// LISTED AS EXERCISE 2 IN LOGBOOK

void setup() {
  // initialize PRIZM
  prizm.PrizmBegin();    
}

void loop() {
  //Repeat 5x
  for(int i = 0; i < 5; i++) {
    // S, repeat 3x short flashes
    for(int j = 0; j < 3; j++ ) {
      prizm.setRedLED(1);
      delay(250);
      prizm.setRedLED(0);
      delay(250);
    }
    // O, repeat 3x long flashes
    for(int j = 0; j < 3; j++ ) {
      prizm.setRedLED(1);
      delay(500);
      prizm.setRedLED(0);
      delay(500);
    }
    // S, repeat 3x short flashes
    for(int j = 0; j < 3; j++ ) {
      prizm.setRedLED(1);
      delay(250);
      prizm.setRedLED(0);
      delay(250);
    }
    // Wait 5 seconds
    delay(5000);
  }
  // End program and reset PRIZM
  prizm.PrizmEnd(); 
}