#ifndef MOTORS_H
#define MOTORS_H

#include <Arduino.h>

// Helper function to convert to steps

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

#endif
