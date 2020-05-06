#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

// Helper function to convert to steps
int angleToSteps(float angle) {
  return (int) (angle / degreesPerStep);
}

// Move passed joints with specified acceleration and to desired joint angles
void moveJoints(AccelStepper joint1, AccelStepper joint2, float * jointAngles, int acceleration) {
  int stepsJ1 = angleToSteps(jointAngles[1]);
  int stepsJ2 = angleToSteps(jointAngles[2]);

  joint1.setAcceleration(acceleration);
  joint2.setAcceleration(acceleration);


  joint1.move(stepsJ1);
  joint2.move(stepsJ2);

   while (
    (joint1.distanceToGo() != 0) ||
    (joint2.distanceToGo() != 0)
    ) {
      joint1.run();
      joint2.run();
  }
}

#endif
