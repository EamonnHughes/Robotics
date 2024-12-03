#include <PRIZM.h>
PRIZM prizm;

// LISTED AS EXERCISE 4 IN LOGBOOK

void setup() {
  // initialize PRIZM
  prizm.PrizmBegin();    
  // Set servo speed
  prizm.setServoSpeed(1, 35);
}

void loop() {
  //Repeat indefinitely
  while (true) {
    // Raise arm
    prizm.setServoPosition(1, 0);
    delay(3000);
    // Lower arm
    prizm.setServoPosition(1, 180);
    delay(3000);
  }
  // End program and reset PRIZM
  prizm.PrizmEnd(); 
}