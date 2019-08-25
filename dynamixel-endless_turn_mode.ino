//Endless turn mode

#include <dxlib.h>

DXLIB dxif (true); // select software serial

uint8_t err;

const int AddValue = 20; 

const int Direction = 1024;

int RotateSpeed = 0;
int i = 0;

void setup() {
  dxif.begin (80000); //Baud Rate is 80000


 //SET to Endless Turn Mode
 //CW Limit -> 0, CCW Limit -> 0
  //CW Angle Limit address is 6, 7
  dxif.WriteWordData (1, 6, 0, NULL);
  //CCW Angle Limit address is 8, 9
  dxif.WriteWordData (1, 8, 0, NULL);
}

void loop(){
  //Rotate to CCW -> Direction = 0
  ////////////////////////////////////////////////////////////////////////////
   //Dynamixel ID is 1
   //LED address is 25
   //Dynamixel's LED ON -> 1
   dxif.WriteByteData (1, 25, 1, &err);

    for(i = 0; i <= 1023; i = i + AddValue){

      RotateSpeed = i;
      //Moving Speed address is 32, 33
      //Speed: 0(0%) ... 1023(100%)
      dxif.WriteWordData (1, 32, RotateSpeed, NULL);
      delay(500);
    }
    
   delay(2000);

  //Rotate to CW -> Direction = 1024
   ///////////////////////////////////////////////////////////////////////
   //Dynamixel ID is 1
   //LED address is 25
   //Dynamixel's LED OFF -> 0
   dxif.WriteByteData (1, 25, 0, &err);

    for(i = 0; i <= 1023; i = i + AddValue){
      
      RotateSpeed = i + Direction; //Because rotate to CW, add 1024
      //Moving Speed address is 32, 33
      //Speed: 0(0%) ... 1023(100%)
      dxif.WriteWordData (1, 32, RotateSpeed, NULL);
      delay(500);
    }
    
   delay(2000);
   //////////////////////////////////////////////////////////////////////
}
