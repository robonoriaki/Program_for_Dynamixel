//Change the position of the motor by pressing the button
//Detects two buttons are pushed. Implemented chattering measures.
#include <dxlib.h>

DXLIB dxif (true); // select software serial

uint8_t err;

//Pull UP
const int buttonON = LOW;
const int buttonOFF = HIGH;

const int button1Pin = 2;
const int button2Pin = 4;

const int RotateValue = 30; 

int button1State = 0;
int button2State = 0;

const int ledPin = 13;

int GoalPosition = 512;

int TargetPosition = 512;


void setup() {
  dxif.begin (80000); //Baud Rate is 80000
  
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  //Initial Position
  //CW Angle Limit address is 6, 7
  dxif.WriteWordData (1, 6, 0, NULL);
  //CCW Angle Limit address is 8, 9
  dxif.WriteWordData (1, 8, 1023, NULL);

  //Goal Position address is 30, 31
  dxif.WriteWordData (1, 30, GoalPosition, NULL);
    
  //Moving Speed address is 32, 33
  //Max Speed -> 0
  dxif.WriteWordData (1, 32, 0, NULL);
}

void loop(){
  //CW Angle Limit address is 6, 7
  //dxif.WriteWordData (1, 6, 0, NULL);
  //CCW Angle Limit address is 8, 9
  //dxif.WriteWordData (1, 8, 1023, NULL);
  
  //read the state of the button1 value
  button1State = digitalRead(button1Pin);
  //read the state of the button2 value
  button2State = digitalRead(button2Pin);


  //pushing button1 and not pushing button2
  if(button1State == buttonON && button2State == buttonOFF){
    //Chattering measures
    delay(10);  //10ms -> 0.010s

    if(button1State == buttonON && button2State == buttonOFF){
      //LED ON
      digitalWrite(ledPin, HIGH);

      //Dynamixel ID is 1
      //LED address is 25
      //Dynamixel's LED OFF -> 0
      dxif.WriteByteData (1, 25, 0, &err);
      
      //Rotate to CW up to - Rotate Value
      TargetPosition = GoalPosition - RotateValue;
      //Goal Position address is 30, 31
      dxif.WriteWordData (1, 30, TargetPosition, NULL);
    
      //Moving Speed address is 32, 33
      //Max Speed -> 0
      dxif.WriteWordData (1, 32, 0, NULL);
    
    }
  
  //not pushing button1 and pushing button2
  }else if(button1State == buttonOFF && button2State == buttonON){
    //Chattering measures
    delay(10);  //10ms -> 0.010s
    
    if(button1State == buttonOFF && button2State == buttonON){
      //LED ON
      digitalWrite(ledPin, HIGH);
      
      //Dynamixel ID is 1
      //LED address is 25
      //Dynamixel's LED OFF
      dxif.WriteByteData (1, 25, 0, &err);
      //Rotate to CW up to + Rotate Value
      TargetPosition = GoalPosition + RotateValue;
      //Goal Position address is 30, 31
      dxif.WriteWordData (1, 30, TargetPosition, NULL);
    
      //Moving Speed address is 32, 33
      //Max Speed -> 0
      dxif.WriteWordData (1, 32, 0, NULL);
    }

  //pushing button1 and pushing button2
  }else if(button1State == buttonON && button2State == buttonON){
    //Chattering measures and Simultaneous pushing measures
    delay(10);  //10ms -> 0.010s

    if(button1State == buttonON && button2State == buttonON){
      digitalWrite(ledPin, LOW);

      //Dynamixel ID is 1
      //LED address is 25
      //DYNAMIXEL's LED ON -> 1
      dxif.WriteByteData (1, 25, 1, &err);
      //Rotate to CW up to GoalPosition
      TargetPosition = GoalPosition;
      //Goal Position address is 30, 31
      dxif.WriteWordData (1, 30, TargetPosition, NULL);
    
      //Moving Speed address is 32, 33
      //Max Speed -> 0
      dxif.WriteWordData (1, 32, 0, NULL);
    }
  
  }else{
    digitalWrite(ledPin, LOW);
    
    //Dynamixel ID is 1
    //LED address is 25
    //DYNAMIXEL's LED OFF -> 0
    dxif.WriteByteData (1, 25, 0, &err);
  }
}
