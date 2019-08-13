/*Motor is rotated alternately CW and CCW direction.*/
/*The motor rotates alternately in the CW and CCW directions.*/
#include <dxlib.h>

DXLIB dxif (true); // select software serial
void setup() {
  dxif.begin (80000); //Baud Rate is 80000
}

void loop(){
  uint8_t err;

  //CW Angle Limit address is 6, 7
  dxif.WriteWordData (1, 6, 0, NULL);
  //CCW Angle Limit address is 8, 9
  dxif.WriteWordData (1, 8, 1023, NULL);

    //Dynamixel ID is 1
    //LED address is 25
    //LED ON -> 1
    dxif.WriteByteData (1, 25, 1, &err);
    
    //Goal Position address is 30, 31
    //Move to 492
    dxif.WriteWordData (1, 30, 492, NULL);
    
    //Moving Speed address is 32, 33
    //Max Speed -> 0
    dxif.WriteWordData (1, 32, 0, NULL);
    
    delay(500);

    //LED OFF -> 0
    dxif.WriteByteData (1, 25, 0, &err);
    
    //Goal Position address is 30, 31
    //Move to 532
    dxif.WriteWordData (1, 30, 532, NULL);

    //Moving Speed address is 32, 33
    dxif.WriteWordData (1, 32, 0, NULL);
    
    delay(500);
  
}

