#define BASE_STEPS 200
#define MICRO_STEPS 0.25

const float stepsPerRotation = BASE_STEPS / MICRO_STEPS;
const float degreesPerStep = 360 / stepsPerRotation;

void setup() 
{

  Serial.begin(9600);
  
  pinMode(6, OUTPUT); //Enable
  pinMode(5, OUTPUT); //Step
  pinMode(4, OUTPUT); //Direction

 digitalWrite(6,LOW);
}

void runMotorv2() {
  int delValue=2000;
  int incValue = 7;
  int accRate=200;
  int totSteps=800;
  for (int i=0; i < totSteps; i++)
  {
   if (totSteps > (2*accRate + 1)){
      if (i < accRate){
        //acceleration
        delValue = delValue - incValue;
      } else if (i > (totSteps - accRate)){
        //decceleration
        delValue = delValue + incValue;
      }
    
    } else {
      //no space for proper acceleration/decceleration
      if (i < ((totSteps - (totSteps % 2))/2)){
        //acceleration
        delValue = delValue - incValue;
      } else if (i > ((totSteps + (totSteps % 2))/2)){
        //decceleration
        delValue = delValue + incValue;
      }
    }
    
    digitalWrite(5, HIGH);
    delayMicroseconds(delValue);
    digitalWrite(5, LOW);
    delayMicroseconds(delValue);
  }  
}

// Function to run the motors to a desired step location
// PARAMETERS:
// * dirPin       : Specifices direction pin on A4988
// * pulsePin     : Specifies the pin to send the pulse to on A4988
// * dir          : (1 or 0) specifies direction of motor
// * totalSteps   : Number of steps to rotate the motor
// * initialPulse : Sets the inital pulse width, speed, of the motor (in ms)
// * rate         : Acceleration rate
void runMotor(int dirPin, int pulsePin, int dir, int totalSteps, int initialPulse, int rate) {
  int pulse = initialPulse;
  int accelRegion = 0.25 * totalSteps;

  // Check direction logic
  if (dir == 1) {  digitalWrite(dirPin, HIGH);  }
  else { digitalWrite(dirPin, LOW); }

  // Stepping logic
  for (int i = 0; i < totalSteps; i++) {

    // Enough room for proper acceleration and deceleration
    if (totalSteps > ( 2 * accelRegion + 1)) {
      // Accelerate during first quarter of steps
      if ( i < (accelRegion) ) { pulse = pulse - rate; }
      // Decelerate during last quarter of steps
      else if ( i > (totalSteps - accelRegion) ) { pulse = pulse + rate; }

    // No space for proper acceleration/decceleration
    } else {
      if (i < ((totalSteps - (totalSteps % 2)) / 2)) { pulse = pulse - rate; } 
      else if (i > ((totalSteps + (totalSteps % 2)) / 2)) { pulse = pulse + rate; }
    }

    // Generate pulse
    digitalWrite(pulsePin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(pulsePin, LOW);
    delayMicroseconds(pulse);
  }
}

int angleToSteps(float angle) {
  return (int) (angle / degreesPerStep);
}


void loop() 
{
  digitalWrite(4,HIGH);

  runMotor(4, 5, 1, angleToSteps(360), 4000, 10);
  runMotor(4, 5, 0, angleToSteps(360), 4000, 10);
  runMotor(4, 5, 1, angleToSteps(95), 4000, 10);


  //runMotorv2();

  Serial.println(angleToSteps(36));
  
  delay(2000);

 
  
/*
  for(Index = 0; Index < 800; Index++)
  {
    digitalWrite(5,HIGH);
    delayMicroseconds(1000);
    digitalWrite(5,LOW);
    delayMicroseconds(1000);
  }
  delay(1000);

  digitalWrite(4,LOW);

  for(Index = 0; Index < 800; Index++)
  {
    digitalWrite(5,HIGH);
    delayMicroseconds(500);
    digitalWrite(5,LOW);
    delayMicroseconds(500);
  }
  delay(1000); */
}
