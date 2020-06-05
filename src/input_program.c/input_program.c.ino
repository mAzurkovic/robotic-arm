#include <AccelStepper.h>
#include "motors.h"
#include "inverse_kinematics.h"

#define LARGE_RATIO 28.44
#define SMALL_RATIO 18.78

#define INTERFACE_TYPE 1

#define J1_DIR  4
#define J1_STEP 5

#define J2_DIR  8
#define J2_STEP 9

#define J3_DIR  11
#define J3_STEP 12

String cmd;

AccelStepper J1 = AccelStepper(INTERFACE_TYPE, J1_STEP, J1_DIR);
AccelStepper J2 = AccelStepper(INTERFACE_TYPE, J2_STEP, J2_DIR);
AccelStepper J3 = AccelStepper(INTERFACE_TYPE, J3_STEP, J3_DIR);

void setup() {
    
  Serial.begin(9600);

  //----------------------------------------------------------------
  //  Setting speed and acceleration parameters for each joint
  //----------------------------------------------------------------
  J1.setMaxSpeed(800.0);
  J1.setAcceleration(800.0);

  J2.setMaxSpeed(800.0);
  J2.setAcceleration(800.0);

  J3.setMaxSpeed(800.0);
  J3.setAcceleration(800.0);
  
  Serial.println("===========");
  Serial.println("Move Joints");
  Serial.println("===========");
  Serial.println("Enter command in form: <J1,J2,J3,J4> <ANGLE>");

  delay(500);
}

void loop() {
  if (Serial.available() > 0) {
    cmd = Serial.readString();    
    String joint = cmd.substring(0,2);
    float angle = (cmd.substring(3)).toFloat();
    
    if (joint.equals("J1")) {
      Serial.println("Moving JOINT 1: " + String(angle) + " degrees");
      moveJoint(J1, angle, 1600, LARGE_RATIO); 
    } else if (joint.equals("J2")) {
      Serial.println("Moving JOINT 2: " + String(angle) + " degrees"); 
      moveJoint(J2, angle, 1600, LARGE_RATIO);
    } else if (joint.equals("J3")) {
      Serial.println("Moving JOINT 3: " + String(angle) + " degrees"); 
      moveJoint(J3, angle, 1600, SMALL_RATIO);
    }

  }

}
