#include <myDuino.h>

myDuino robot(1);

//Declare and Initialize Variables

//Boolean state for if system is started
boolean systemStarted = false;
//Button for starting system
int but1 = 0;
//Ultrasonic value for detecting platform
unsigned long ultrasonicVal = 0;
//Boolean state for if platform is detected
boolean platformDetected = false;
//Button for long arm roller switch
int but2 = 0;
//Integer value representing if the roller switch was hit once
int hitOnce = 0;
//Timer for returning the RC cars
unsigned long timer1 = 9999999;
//Boolean state for if RC cars are returned
boolean returnedCars = false;
//Boolean state for if Buzz is detected
boolean buzzDetected = false;
//Boolean state for if in start zone
boolean outOfCircle = false;
//Boolean state for if robot is out of start zone
boolean inArena = false;
//Boolean state for if robot began moving out of start zone
boolean startedMoving = false;
//Timer to move into arena
unsigned long timer2 = 9999999;
//Boolean state for whether the rocket has started lifting
boolean startLift = false;
//Timer for lifting rocket
unsigned long timer3 = 9999999;
//Boolean state for if rocket is lifted
boolean rocketLifted = false;
//Timer for system
unsigned long systemTimer = 9999999;
//Boolean state for if system timer has started
boolean timerStarted = false;

void setup() {

  Serial.begin(9600);
}

void loop() {

  if (!systemStarted) {
    startSystem();
  }
  
  else if (systemStarted && !platformDetected) {
    
    robot.moveMotor(1,1,255);
    detectPlatform();
  }
  
  else if (platformDetected && !returnedCars) {
  
    robot.moveMotor(1,1,0);
    releaseCars();

  }
  else if (returnedCars && !buzzDetected) {

    robot.moveMotor(1,2,255);
    detectBuzz();
  }

  else if (buzzDetected && !outOfCircle) {

    dropArm();
    detectCircleRange();
  }
  
  else if (outOfCircle && !inArena) {

    robot.moveMotor(1,1,255);
    moveToArena();
  }  
  
  else if (inArena) {

    robot.moveMotor(1,1,0);
  }

  if (millis() < systemTimer) {
    
    if (platformDetected) {

      liftRocket();
    }
  }
  else {
    stopSystem();
  }
}

//METHODS

void startSystem() {

  but1 = robot.readButton(5);
  if (but1 == 1) {
    systemStarted = true;

    if (!timerStarted) {
      systemTimer = millis() + 37000;
      timerStarted = true;
    }
    
  }
}

void detectPlatform() {

  ultrasonicVal = robot.readUltrasonic();
  Serial.println("Ultra val: " + String(ultrasonicVal));
  if (ultrasonicVal <= 9) {
    platformDetected = true;
  }
  
}

void releaseCars() {

  but2 = robot.readButton(4);
  
  if (but2 == 1) {

    hitOnce++;

    if (hitOnce == 1) {
      timer1 = millis() + 1500;
      robot.digital(2,1);
    }
  }

  if (millis() >= timer1) {

    returnedCars = true;
  }

}

void detectBuzz() {

  ultrasonicVal = robot.readUltrasonic();
  if (ultrasonicVal >= 11) {
    buzzDetected = true;
  }
}

void dropArm() {

  robot.digital(1,1);
}

void detectCircleRange() {

  ultrasonicVal = robot.readUltrasonic();
  Serial.println("Ultra val: " + String(ultrasonicVal));
  if (ultrasonicVal >= 40) {
    outOfCircle = true;
  }
}

void moveToArena() {

  if (!startedMoving) {
    timer2 = millis() + 1500;
    startedMoving = true;
  }

  if (millis() >= timer2) {

    inArena = true;
  }
}

void liftRocket() {

  robot.moveMotor(2,1,255);
}

void stopSystem() {

  robot.moveMotor(1,1,0);
  robot.moveMotor(2,1,0);
  robot.digital(1,0);
  robot.digital(2,0);
}
