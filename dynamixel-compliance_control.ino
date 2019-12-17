//Compliance control

#include <dxlib.h>

DXLIB dxif (true); // select software serial

uint8_t err;

const int AddValue = 20; 
const int Direction = 1024;
const int ID = 1;


int TargetPosition = 512;
int GoalPosition = 512;
int RotateSpeed = 0;
int PresentLoad = 0;

void setup() {
  dxif.begin (80000); //Baud Rate is 80000
  Serial.begin(9600);

 //Set angle limit
 //CW Limit -> 0, CCW Limit -> 1023
  //CW Angle Limit address is 6, 7
  //WordDataは16ビットのデータをやるときに使う
  //ByteDataは8ビットのデータをやるときに使う
  dxif.WriteWordData (ID, 6, 0, NULL);
  //CCW Angle Limit address is 8, 9
  dxif.WriteWordData (ID, 8, 1023, NULL);

  //Move to initial position
  //Goal Position address is 30, 31
  dxif.WriteWordData (ID, 30, GoalPosition, NULL);

  //Set moving speed
  //Moving Speed address is 32, 33
  //Max Speed -> 0
  dxif.WriteWordData (ID, 32, 0, NULL);

  //Goal Position から指定した範囲内でコンプライアンス制御をする
  //Set CW Compliance Margin(0-254) Goal Positionからの動作可能範囲
  //Address is 26
  dxif.WriteByteData(ID, 26, 100, NULL);

  //Set CCW Compliance Margin(0-254)
  //Address is 27
  dxif.WriteByteData(ID, 27, 100, NULL);
  
  //Set CW Compliance Slope(1-254) コンプライアンスの度合い
  //大きい値ほどスロープが長くなるので、柔らかくなるように感じる
  //Address is 28
  dxif.WriteByteData(ID, 28, 50, NULL);
  
  //Set CCW Compliance Slope(1-254)
  //Address is 29
  dxif.WriteByteData(ID, 29, 50, NULL);
}

void loop(){
  //Goal Position address is 30, 31
  //dxif.WriteWordData (ID, 30, GoalPosition, NULL);
  
  //Read present load
  //Present Load address is 40,41
  dxif.ReadWordData (ID, 40, &PresentLoad, NULL);

  //Dsplay present load
  Serial.print("load: ");
  Serial.print(PresentLoad);
  Serial.print("\n");
  
}
