#include<Servo.h>

//#define switch_pin 10


Servo Flame;
int switch_pin = 10;
int signal_pin = 3;
int LED_B_pin = 2;
int LED_G_pin = 5;
int c = 0;


void setup()
{
  Serial.begin(9600);
  Flame.attach(signal_pin);
  pinMode(switch_pin, INPUT_PULLUP);
  pinMode(LED_B_pin, OUTPUT);
  pinMode(LED_G_pin, OUTPUT);
  Flame.write(1000);
}

void loop()
{
   if(digitalRead(switch_pin) == 0)
   {
    Flame.write(1000);
    delay(1000);
    c = 0;
    switch(c)
    {
    case 0:
    digitalWrite(LED_B_pin, HIGH);
    for(int i=1000; i<1184; i+=2)
    {
      Flame.write(i);
//      Serial.print(i);
      delay(100);
    }
    c = 1;

    case 1:
    digitalWrite(LED_B_pin, LOW);
    delay(1000);
    digitalWrite(LED_G_pin, HIGH);
    for(int i=1184; i<1200; i++)
    {
      Flame.write(i);
//      Serial.print(i);
//      Serial.println();
      delay(100);
    }
    delay(2500);
    for(int i= 1200; i>1184; i--)
    {
      Flame.write(i);
//      Serial.print(i);
//      Serial.println();
      delay(100);
    }
      digitalWrite(LED_G_pin, LOW);
    }
    Flame.write(1180);
  }
}
