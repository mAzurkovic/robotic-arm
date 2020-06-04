#include <AccelStepper.h>

AccelStepper J1 = AccelStepper(1, 4, 5);


void setup() {
  // put your setup code here, to run once:
  J1.setMaxSpeed(800);
    J1.setSpeed(800);
  J1.setAcceleration(800.0);

}

void loop() {
  // put your main code here, to run repeatedly:
  J1.runSpeed();
}
