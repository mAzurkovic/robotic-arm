#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

#define BASE_STEPS 200
#define MICRO_STEPS 0.25
#define MAX_SPS 800

#define LARGE_RATIO 28.44
#define SMALL_RATIO 18.78

const float stepsPerRotation = BASE_STEPS / MICRO_STEPS;
const float degreesPerStep = 360 / stepsPerRotation;


// Helper function to convert to steps
int angleToSteps(float angle) {
  return (int) (angle / degreesPerStep);
}

void moveJoints(AccelStepper joint1, AccelStepper joint2, AccelStepper joint3, float * jointAngles, int acceleration) {
	int stepsJ1 = angleToSteps(jointAngles[0]) * LARGE_RATIO;
	int stepsJ2 = angleToSteps(jointAngles[1]) * LARGE_RATIO;
	int stepsJ3 = angleToSteps(360 - jointAngles[2]) * SMALL_RATIO;


	joint1.setAcceleration(acceleration);
	joint2.setAcceleration(acceleration);
	joint3.setAcceleration(acceleration);


	joint1.move(stepsJ1);
	joint2.move(stepsJ2);
	joint3.move(stepsJ3);

	while (
		(joint1.distanceToGo() != 0) ||
		(joint2.distanceToGo() != 0) ||
		(joint3.distanceToGo() != 0)
		) {
		joint1.run();
		joint2.run();
		joint3.run();
	}
}

void moveJoint(AccelStepper joint, float angle, int acceleration, float ratio) {  
  int steps = angleToSteps(angle) * ratio;

  joint.setAcceleration(acceleration);
  joint.move(steps);

  while (joint.distanceToGo() != 0) {
      joint.run();
  }
} 

#endif
