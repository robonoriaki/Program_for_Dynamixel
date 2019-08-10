#include <dxlib.h>

DXLIB dxif (true); // select software serial
void setup() {
  dxif.begin (80000);
}

void loop(){
  uint8_t err;

  dxif.WriteWordData (1, 6, 0, NULL);
  dxif.WriteWordData (1, 8, 1023, NULL);
  
    //LED ON
    dxif.WriteByteData (1, 25, 1, &err);
    //Move to 200
    dxif.WriteWordData (1, 30, 492, NULL);
    dxif.WriteWordData (1, 32, 0, NULL);
    delay(500);

    //LED OFF
    dxif.WriteByteData (1, 25, 0, &err);
    //Move to 400
    dxif.WriteWordData (1, 30, 532, NULL);
    dxif.WriteWordData (1, 32, 0, NULL);
    delay(500);
  
}

