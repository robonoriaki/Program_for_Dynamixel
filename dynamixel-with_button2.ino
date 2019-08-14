
#include <dxlib.h>

DXLIB dxif (true); // select software serial

uint8_t err;

//Pull UP
const int buttonON = LOW;
const int buttonOFF = HIGH;

const int button1Pin = 2;
const int button2Pin = 4;

int button1State = 0;
int button2State = 0;

const int ledPin = 13;

void setup() {
  dxif.begin (80000); //Baud Rate is 80000
  Serial.begin(9600);
  
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop(){
  
  //read the state of the button1 value
  button1State = digitalRead(button1Pin);
  //read the state of the button2 value
  button2State = digitalRead(button2Pin);

  //display on serial monitor
  Serial.print("button1: ");
  Serial.print(button1State);
  Serial.print("     ");
  Serial.print("button2: ");
  Serial.print(button2State);
  Serial.print("\n");

  //pushing button1 and not pushing button2
  if(button1State == buttonON && button2State == buttonOFF){
    digitalWrite(ledPin, HIGH);
    
    //Dynamixel's LED OFF -> 0
    dxif.WriteByteData (1, 25, 0, &err);

  //not pushing button1 and pushing button2
  }else if(button1State == buttonOFF && button2State == buttonON){
    digitalWrite(ledPin, HIGH);
    
    //Dynamixel ID is 1
    //LED address is 25
    //LED ON -> 1
    dxif.WriteByteData (1, 25, 1, &err);
  
  }else{
    digitalWrite(ledPin, LOW);
    delay(100);
  }
}

