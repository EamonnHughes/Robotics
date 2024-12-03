#include <PRIZM.h>

PRIZM prizm;
int Power = 20;

void setup() {
  prizm.PrizmBegin();
  prizm.setMotorInvert(2, 1);
}

void loop() {
  Power = (prizm.readSonicSensorCM(2));

  prizm.setMotorPowers(Power, Power);

}
