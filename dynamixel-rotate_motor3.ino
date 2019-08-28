//Alternately rotate infinitely between CW and CCW
//Use function
#include <dxlib.h>


DXLIB dxif (true); // select software serial


void SetAngleLimit(int ID, int CWLimit, int CCWLimit){
  //CW Angle Limit address is 6, 7
  dxif.WriteWordData (ID, 6, CWLimit, NULL);
  //CCW Angle Limit address is 8, 9
  dxif.WriteWordData (ID, 8, CCWLimit, NULL);
}

void MoveToGoalPosition(int ID, int GoalPosition, int MovingSpeed){
  //Goal Position address is 30, 31
  //Move to 492
  dxif.WriteWordData (ID, 30, GoalPosition, NULL);
    
  //Moving Speed address is 32, 33
  //Max Speed -> 0
  dxif.WriteWordData (ID, 32, MovingSpeed, NULL);
}

void EndlessTurn(int ID, int RotateSpeed, int Direction){
  int SpeedAndDirection;

  //Rotate Speed: 0(0%) ... 1023(100%)
  //Rotate to CW -> Direction = 1024, Rotate to CCW -> Direction = 0
  SpeedAndDirection = RotateSpeed + Direction;

  //Moving Speed address is 32, 33
  dxif.WriteWordData (1, 32, SpeedAndDirection, NULL);
  
}

int ID = 1;
int AngleLimitCW = 0;
int AngleLimitCCW = 0;
int RotateSpeed = 512;
int RotateDirection = 0;

uint8_t err;

void setup() {
  dxif.begin (80000); //Baud Rate is 80000

  SetAngleLimit(ID, AngleLimitCW, AngleLimitCCW);
}


void loop() {
  //Dynamixel ID is 1
  //LED address is 25
  //LED ON -> 1
  dxif.WriteByteData (ID, 25, 1, &err);

  //Rotate to CW
  RotateDirection = 1024;
  EndlessTurn(ID, RotateSpeed, RotateDirection);

  delay(5000);

  //LED OFF -> 0
  dxif.WriteByteData (ID, 25, 0, &err);

  //Rotate to CW
  RotateDirection = 0;
  EndlessTurn(ID, RotateSpeed, RotateDirection);

  delay(5000);
  
}
