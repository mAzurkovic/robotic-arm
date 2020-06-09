#include <AccelStepper.h>

#define RATIO 28.44

#define BASE_STEPS 200
#define MICRO_STEPS 0.25
#define MAX_SPS 800

#define J1_DIR  4
#define J1_STEP 5

AccelStepper J1 = AccelStepper(1, J1_STEP, J1_DIR);

const float stepsPerRotation = BASE_STEPS / MICRO_STEPS;
const float degreesPerStep = 360 / stepsPerRotation;

int angleToSteps(float angle) {
  return (int) (RATIO * angle / degreesPerStep);
}


void moveJoint(AccelStepper joint1, float stepsJ1, int acceleration) {  
  joint1.setAcceleration(acceleration);
  
  joint1.move(stepsJ1);

   while ( (joint1.distanceToGo() != 0) ) {
      joint1.run();
  }
} 


void run3(int distance, int initialVelocity, int finalVelocity, int acceleration) {
  unsigned long time;
  unsigned long previousAccel = 0;
  int interval = 100;  // # of milliseconds between speed increases
  int makeSpeed;

  J1.move(distance);
  J1.setSpeed(initialVelocity);

   while (J1.distanceToGo() != 0) {
    time = millis();
    if (time > previousAccel + interval) {
      previousAccel = time;

      // Acceleration logic
      if (finalVelocity > initialVelocity) {          // Accelerate
        //J1.setSpeed(J1.speed() + acceleration); 
        makeSpeed = (J1.speed() > MAX_SPS) ? MAX_SPS : J1.speed() + acceleration;
      } else if (finalVelocity < initialVelocity) {   // Deccelerate
        //J1.setSpeed(J1.speed() - acceleration); 
        makeSpeed = (J1.speed() > MAX_SPS) ? MAX_SPS : J1.speed() - acceleration;
      } else {
        //J1.setSpeed(finalVelocity);                   // Run at constant speed  
         makeSpeed = (J1.speed() > MAX_SPS) ? MAX_SPS : finalVelocity;
      }
      J1.setSpeed(makeSpeed);
    }
    J1.runSpeed();
  }

}

void setup() {
  // put your setup code here, to run once:
  J1.setMaxSpeed(800);
  J1.setAcceleration(400.0);

}

void loop() {
  
  // put your main code here, to run repeatedly:
  
  run3(800, 0, 800, 10);
  delay(500);
}
