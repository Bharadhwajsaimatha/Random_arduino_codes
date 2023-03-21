/*
  Mega analogWrite() test

  This sketch fades LEDs up and down one at a time on digital pins 2 through 13.
  This sketch was written for the Arduino Mega, and will not work on other boards.

  The circuit:
  - LEDs attached from pins 2 through 13 to ground.

  created 8 Feb 2009
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogWriteMega
*/

// These constants won't change. They're used to give names to the pins used:
const int lowestPin = 3;
const int highestPin = 11;


void setup() {
    pinMode(lowestPin, OUTPUT);
    pinMode(highestPin, OUTPUT);
 
}

void loop() {
  int brightness = 127;
   analogWrite(highestPin, 0);
   delay(1);
      analogWrite(lowestPin, brightness);
      delay(100);
      analogWrite(lowestPin, 0);
      delay(1);
      analogWrite(highestPin, brightness);
      delay(100);
}
