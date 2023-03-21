#include <Servo.h>

// Connect the servo signal pin on D2
#define Servopin 2
Servo GGservo;

void setup() {
  Serial.begin(9600);
  GGservo.attach(Servopin);

  // put your setup code here, to run once:

}

void loop() {
  GGservo.write(0);
  
  // put your main code here, to run repeatedly:

}
