int Index;

void setup() 
{
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

void runMotor(int pulsePin, int totalSteps, int initialPulse, int rate) {
  int pulse = initialPulse;
  int accelRegion = 0.25 * totalSteps;

  for (int i = 0; i < totalSteps; i++) {

    // Accelerate during first quarter of steps
    if ( i < (accelRegion) ) { pulse = pulse - rate; }
    // Decelerate during last quarter of steps
    else if ( i > (totalSteps - accelRegion) ) { pulse = pulse + rate; }


    // Generate pulse
    digitalWrite(pulsePin, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(pulsePin, LOW);
    delayMicroseconds(pulse);
  }
}

void loop() 
{
  digitalWrite(4,HIGH);

  runMotor(5, 800, 2000, 7);
  //runMotorv2();
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
