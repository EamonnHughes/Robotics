 #include <PRIZM.h>
 PRIZM prizm;
 
 void setup() {

  prizm.PrizmBegin();

}

void loop() {

  while (prizm.readStartButton() == 1) {
    prizm.setGreenLED(HIGH);
    delay(300);
    prizm.setGreenLED(LOW);
    delay(300);
  }

}
