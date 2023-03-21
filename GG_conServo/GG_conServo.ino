#include <Servo.h>

// Connect the servo signal pin on D2
#define Servopin 2

//Buttons to control the roation angle
#define Button1 5
#define Button2 6
#define Button3 7
#define Button4 8

//Creating a Servo object as GGservo
Servo GGservo;

//Count to change the direction of rotation
int count = 0;
int val = 0;

void setup() 
{
  Serial.begin(9600);
  GGservo.attach(Servopin);

  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);
  pinMode(Button4, INPUT_PULLUP);
  
  GGservo.write(1500);
}

void loop() {
  // Assigning value to the button press
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
 if(digitalRead(Button4) == 0)
 {
  val=4;
 }
 
 switch(val)
 {
  case 1:
  
  GGservo.write(1500);
  delay(200);
  Serial.println("At neutral position");
  break;

  case 2:
 
  GGservo.write(1600);
  delay(1000);
  Serial.println("Rotated in clockwise");
  break;

  case 3:
 
  GGservo.write(1600);
  delay(1500);
  Serial.println("Rotated in Anti-clockwise");
  break;

  case 4:

  GGservo.write(1600);
  delay(3000);
  break;
 }
 val = 0;
 GGservo.write(1500);
 Serial.println("Servo stopped");
 delay(1000);
}
