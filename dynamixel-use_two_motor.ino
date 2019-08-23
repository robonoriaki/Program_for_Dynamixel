//Change the position of the motor by pressing the button
//Detects two buttons are pushed. Implemented chattering measures.
//Use two Dynamixel
#include <dxlib.h>

DXLIB dxif (true); // select software serial

uint8_t err;

const int RotateValue = 50; 

int GoalPosition = 512;

int TargetPosition1 = 512;
int TargetPosition2 = 512;


void setup() {
  dxif.begin (57143); //Baud Rate is 57143

  //Initial Position ID 1
  //CW Angle Limit address is 6, 7
  dxif.WriteWordData (1, 6, 0, NULL);
  //CCW Angle Limit address is 8, 9
  dxif.WriteWordData (1, 8, 1023, NULL);

  //Goal Position address is 30, 31
  dxif.WriteWordData (1, 30, GoalPosition, NULL);
    
  //Moving Speed address is 32, 33
  //Max Speed -> 0
  dxif.WriteWordData (1, 32, 0, NULL);

  //Initial Position ID 2
  //CW Angle Limit address is 6, 7
  dxif.WriteWordData (2, 6, 0, NULL);
  //CCW Angle Limit address is 8, 9
  dxif.WriteWordData (2, 8, 1023, NULL);

  //Goal Position address is 30, 31
  dxif.WriteWordData (2, 30, GoalPosition, NULL);
    
  //Moving Speed address is 32, 33
  //Max Speed -> 0
  dxif.WriteWordData (2, 32, 0, NULL);
}

void loop(){
  ////////////////////////////////////////////////////////////////////////////
   //Dynamixel ID is 1
   //LED address is 25
   //Dynamixel's LED ON -> 1
   dxif.WriteByteData (1, 25, 1, &err);

   //Dynamixel ID is 2
   //LED address is 25
   //Dynamixel's LED OFF -> 0
   dxif.WriteByteData (2, 25, 0, &err);
      
   //Rotate to CW up to - Rotate Value
   TargetPosition1 = GoalPosition - RotateValue;
   //Goal Position address is 30, 31
   dxif.WriteWordData (1, 30, TargetPosition1, NULL);
    
   //Moving Speed address is 32, 33
   //Max Speed -> 0
   dxif.WriteWordData (1, 32, 0, NULL);

   //Rotate to CW up to + Rotate Value
   TargetPosition2 = GoalPosition + RotateValue;
   //Goal Position address is 30, 31
   dxif.WriteWordData (2, 30, TargetPosition2, NULL);
    
   //Moving Speed address is 32, 33
   //Max Speed -> 0
   dxif.WriteWordData (2, 32, 0, NULL);

   delay(1000);

   ///////////////////////////////////////////////////////////////////////
   //Dynamixel ID is 1
   //LED address is 25
   //Dynamixel's LED OFF -> 0
   dxif.WriteByteData (1, 25, 0, &err);

   //Dynamixel ID is 2
   //LED address is 25
   //Dynamixel's LED ON -> 1
   dxif.WriteByteData (2, 25, 1, &err);
      
   //Rotate to CW up to + Rotate Value
   TargetPosition1 = GoalPosition + RotateValue;
   //Goal Position address is 30, 31
   dxif.WriteWordData (1, 30, TargetPosition1, NULL);
    
   //Moving Speed address is 32, 33
   //Max Speed -> 0
   dxif.WriteWordData (1, 32, 0, NULL);

   //Rotate to CW up to - Rotate Value
   TargetPosition2 = GoalPosition - RotateValue;
   //Goal Position address is 30, 31
   dxif.WriteWordData (2, 30, TargetPosition2, NULL);
    
   //Moving Speed address is 32, 33
   //Max Speed -> 0
   dxif.WriteWordData (2, 32, 0, NULL);

   delay(1000);
   //////////////////////////////////////////////////////////////////////
}
