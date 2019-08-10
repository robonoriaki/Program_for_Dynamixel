#include <dxlib.h>
DXLIB dxif (true); // select software serial
void setup() {
  dxif.begin (80000);
}

void loop(){
  uint8_t led;
  uint8_t err;
  int i;

  //Read value
  dxif.ReadByteData (1, 25, &led, NULL);
  delay(500);
  
  for(i = 0; i < 20; i++){
    //LED ON
    dxif.WriteByteData (1, 25, 1, &err);
    delay(500);
    //LED OFF
    dxif.WriteByteData (1, 25, 0, &err);
    delay(500);
  }
  delay(500);
  
}

