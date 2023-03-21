#include <Servo.h>

//Buttons to control the roation angle
#define Button1 5
#define Button2 6
#define Button3 7

//Connect servo to D2

#define ServoPin 2

Servo GGservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int val = 0;    // variable to store the servo position

void setup()
{
  Serial.begin(9600);
  
  GGservo.attach(ServoPin);  // attaches the servo on pin D2 to the servo object
  
  pinMode(Button1, INPUT_PULLUP);
  pinMode(Button2, INPUT_PULLUP);
  pinMode(Button3, INPUT_PULLUP);

  GGservo.write(90);
  delay(100);
  GGservo.write(0);
  delay(1000);
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
 
 switch(val)
 {
  case 1:
  GGservo.write(90);
  delay(1000);
  Serial.println("Rotated 120 degrees");
  break;

  case 2:
  GGservo.write(145);
  delay(1000);
  Serial.println("Rotated 150 degrees");
  break;

  case 3:
  GGservo.write(180);
  delay(2000);
  Serial.println("Rotated 180 degrees");
  break;
 }
 val = 0;
 delay(2000);

}
