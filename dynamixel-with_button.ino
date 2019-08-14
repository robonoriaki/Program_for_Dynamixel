/*First, turn on the built-in LED of Arduino with Dynamixel Library*/

#include <dxlib.h>

DXLIB dxif (true); // select software serial

uint8_t err;

//Pull UP
const int buttonON = LOW;
const int buttonOFF = HIGH;

const int button1Pin = 2;
const int button2Pin = 4;

int button1State = HIGH;
int button2State = HIGH;

const int ledPin = 13;

void setup() {
  dxif.begin (80000); //Baud Rate is 80000
  
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop(){
  
  //read the state of the button1 value
  button1State = digitalRead(button1Pin);
  //read the state of the button2 value
  button2State = digitalRead(button2Pin);

  
  if(button1State == buttonON){
    digitalWrite(ledPin, LOW);
    //LED OFF -> 0
    dxif.WriteByteData (1, 25, 0, &err);
    
    delay(100);
    
  }else{
    digitalWrite(ledPin, HIGH);
    //Dynamixel ID is 1
    //LED address is 25
    //LED ON -> 1
    dxif.WriteByteData (1, 25, 1, &err);

    delay(100);
  
  }
}

