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
  
    //LED ON
    //LED address is 25
    //Dynamixel ID is 1
    dxif.WriteByteData (1, 25, 1, &err);
    
    //Move to 492
    //Goal Position address is 30, 31
    dxif.WriteWordData (1, 30, 492, NULL);
    
    //Moving Speed address is 32, 33
    dxif.WriteWordData (1, 32, 0, NULL);
    
    delay(500);

    //LED OFF
    dxif.WriteByteData (1, 25, 0, &err);
    
    //Move to 532
    //Goal Position address is 30, 31
    dxif.WriteWordData (1, 30, 532, NULL);

    //Moving Speed address is 32, 33
    dxif.WriteWordData (1, 32, 0, NULL);
    
    delay(500);
  
}

