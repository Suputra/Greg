#include <myDuino.h>

myDuino robot(1);
int but4;
int but5;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  but4 = robot.readButton(4);
  but5 = robot.readButton(1);
  if (but5 == 1) {
      robot.moveMotor(2,1,255);
  } else if (but4 == 1) {
    robot.moveMotor(2,2,255);
  } else {
    robot.moveMotor(2,1,0);
  }
  but4 = 0;
  but5 = 0;
  delay(100);
}
