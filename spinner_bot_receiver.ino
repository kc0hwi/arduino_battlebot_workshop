#include <SPI.h>      //SPI library for communication with the nRF24L01+
#include "RF24.h"  //The main library of the nRF24L01+
#include "Wire.h"


RF24 radio (7, 8); // CE,CSN

//Create a pipe addresses for  communication
const uint64_t pipe = 3737;

struct JoystickData {
  int X;
  int Y;
  bool buttonState;
} joystickData;

//typedef struct package Package;
//Package pos;

int buttonState;
int spinnerState = false ;
int motora_1 = 3;
int motora_2 = 4;
int motorb_1 = 5;
int motorb_2 = 6;
int spinner = 2;



void setup()
{
  Serial.begin(9600);
  radio.begin();                    //Start the nRF24 communicate
  radio.openReadingPipe(1, pipe);   //Sets the address of the transmitter to which the program will receive data.
  radio.startListening();
  pinMode(motora_1, OUTPUT);
  pinMode(motora_2, OUTPUT);
  pinMode(motorb_1, OUTPUT);
  pinMode(motorb_2, OUTPUT);
  pinMode(spinner, OUTPUT);
  digitalWrite(spinner, LOW);
  delay(100);
}

void loop()
{

  if (radio.available()) {
    radio.read(&joystickData, sizeof(joystickData));
    
    // Process and use the received joystick data as needed
    
//    Serial.print("X:");
//    Serial.println(pos.X);

//    Serial.print("      buttonState");
//    Serial.println(buttonState);
  }

  int xAxis = joystickData.X;
  int yAxis = joystickData.Y;
  bool buttonState = joystickData.buttonState;
  Serial.print("X:");
  Serial.println(joystickData.X);
  Serial.print(" Y ");
  Serial.println(joystickData.Y);
//  int forward = map(yAxis, 570, 1024, 0, 255);
//  int backward = map(yAxis, 480, 0, 0, 255);
  // For some reason, the joystick hits 0 when all the way forward
  int backward = map(yAxis, 570, 1024, 0, 255);
  int forward = map(yAxis, 480, 0, 0, 255);
  int right = map(xAxis, 570, 1024, 0, 255);
  int left = map(xAxis, 480, 0, 0, 255);

// Move forward
  if (yAxis == 0) {
    // Set Motor A stop
    analogWrite(motora_1, 0);
    analogWrite(motora_2, 0);
    // Set Motor B stop
    analogWrite(motorb_1, 0);
    analogWrite(motorb_2, 0);    
  }else if (yAxis < 480) {                  // Move forward
    // Set Motor A forward
    analogWrite(motora_1, forward);
    analogWrite(motora_2, 0);
    // Set Motor B forward
    analogWrite(motorb_1, forward);
    analogWrite(motorb_2, 0);
  } else if (yAxis > 550) {           // Move backwards
    // Set Motor A backward
    analogWrite(motora_1, 0);
    analogWrite(motora_2, backward);
    // Set Motor B backward
    analogWrite(motorb_1, 0);
    analogWrite(motorb_2, backward);    
  } else if (xAxis > 570) {           // Move right
    // Set Motor A forward
    analogWrite(motora_1, right);
    analogWrite(motora_2, 0);
    // Set Motor B stop
    analogWrite(motorb_1, 0);
    analogWrite(motorb_2, 0); 
  } else if (xAxis < 480 ){           // Move left
    // Set Motor A stop
    analogWrite(motora_1, 0);
    analogWrite(motora_2, 0);
    // Set Motor B foward
    analogWrite(motorb_1, left);
    analogWrite(motorb_2, 0);   
  } else {
    // Set Motor A stop
    analogWrite(motora_1, 0);
    analogWrite(motora_2, 0);
    // Set Motor B stop
    analogWrite(motorb_1, 0);
    analogWrite(motorb_2, 0);    
  }

    Serial.print("button state: ");
    Serial.println(buttonState);
    if (buttonState == 0 ) {
      spinnerState = ! spinnerState;
      delay(50);
    }
//
    if (spinnerState == true) {
      digitalWrite(spinner, HIGH);              // Turn On spinner
      delay(50);
    } else {
      digitalWrite(spinner, LOW);               // Turn Off spinner
      delay(50);
    }

// Testing
// Forward
    // Set Motor A forward
    //analogWrite(motora_1, 255);
    //analogWrite(motora_2, 0);
    // Set Motor B forward
    //analogWrite(motorb_1, 255);
    //analogWrite(motorb_2, 0);
// Right
    // Set Motor A forward
    //analogWrite(motora_1, right);
    //analogWrite(motora_2, 0);
    // Set Motor B stop
    //analogWrite(motorb_1, 0);
    //analogWrite(motorb_2, 0);
}
