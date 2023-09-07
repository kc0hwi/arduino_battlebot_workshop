/* YOU HAVE TO INSTALL THE RF24 LIBRARY BEFORE UPLOADING THE CODE
   https://github.com/tmrh20/RF24/      
*/

#include <SPI.h>        //SPI library for communicate with the nRF24L01+
#include "RF24.h"       //The main library of the nRF24L01+

RF24 radio(7, 8);

//Create a pipe addresses for  communication
const uint64_t pipe = 0xE8E8F0F0E1LL;


struct package
{
  int X=1;
  int Y=1;
};

//typedef struct package Package;
//Package pos;
struct JoystickData {
  int X;
  int Y;
  bool buttonState;
} joystickData;

int xPin = A0;
int yPin = A1;

int rawY;
int mappedY;

int buttonPin = 2;
int buttonState;

void setup() {
  Serial.begin(9600);
  radio.begin();                 //Start the nRF24 communicate
  radio.openWritingPipe(pipe);   //Sets the address of the receiver to which the program will send data.
  
  pinMode(buttonPin, INPUT_PULLUP); // Activate pull-up resistor on the push button pin
  
}

void loop() {

  joystickData.X = analogRead(xPin); // Read Joysticks X-axis
  rawY = analogRead(yPin);
  mappedY = map(rawY, 0, 1024, 1, 1024);
  joystickData.Y = mappedY; // Read Joysticks Y-axis
  joystickData.buttonState = digitalRead(buttonPin);
  // X value
  Serial.print("X:");
  Serial.println(joystickData.X);
  Serial.print("    Y");
  Serial.println(joystickData.Y);
//  Serial.print("    button");
//  Serial.println(buttonState);
 
  radio.write(&joystickData, sizeof(joystickData)); // Send data  to the other NRF24L01 module
  //radio.write(&buttonState, sizeof(buttonState));
  delay(300);
  
}
