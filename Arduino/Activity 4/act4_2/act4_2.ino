#include <PRIZM.h>

PRIZM prizm;
int Power = 20;

void setup() {
  prizm.PrizmBegin();
  prizm.setMotorInvert(2, 1);
}

void loop() {
  prizm.setMotorPowers(Power, Power);
  delay(3000);
  prizm.setMotorPowers(Power + 10, Power + 10);
  delay(3000);
  prizm.setMotorPowers(Power - 10, Power - 10);
  delay(3000);
  prizm.setMotorPowers(125, 125);

  prizm.PrizmEnd();
}
