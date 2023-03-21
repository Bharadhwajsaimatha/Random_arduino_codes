// Arduino stepper motor control code

#include <Stepper.h> // Include the header file

// change this to the number of steps on your motor
#define STEPS 32

//Buttons to control the roation angle
#define Button1 5
#define Button2 6
#define Button3 7

// Stepper Instance
Stepper stepper(STEPS, 8, 10, 9, 11);

int val;

void setup() {
  Serial.begin(9600);
  
  stepper.setSpeed(1080);
  
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
}

void loop() {
//
//  if (Serial.available()>0)
//  {
//    val = Serial.parseInt();
//    stepper.step(val);
//    Serial.println(val); //for debugging
//  }
 if(digitalRead(Button1) == 0)
 {
  val=1;
 }
 if(digitalRead(Button2) == 0)
 {
  val=2;
 }
 if(digitalRead(Button3) == 0)
 {
  val=3;
 }
 switch(val)
 {
  case 1:
  stepper.step(171);
  Serial.println("Rotated 30 degrees");
  break;

  case 2:
  stepper.step(682);
  Serial.println("Rotated 120 degrees");
  break;

  case 3:
  stepper.step(1366);
  Serial.println("Rotated 240 degrees");
  break;
 }
 val = 0;
 delay(2000);

}
