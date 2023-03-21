#include <Servo.h>

#define C_pin A1
#define Testpin 2
#define noofesc 5

Servo Flame[noofesc];
int signalpin[noofesc] = {5,6,8,9,10};
int count = 0;


void setup() 
{
  Serial.begin(9600);
  for(int i=0; i<noofesc; i++)
  {
    Flame[i].attach(signalpin[i]);
  }
  pinMode(Testpin, INPUT_PULLUP);
  pinMode(C_pin, INPUT);
}

void loop() 
{
  if(digitalRead(Testpin) == 0)
  {
    for(int i=1182;i<=1200;i++)
    {
      for(int j=0;j<noofesc;j++)
      {
        Serial.print(" Increasing PWM\n");
        Flame[j].write(i);
        delay(100);
        Serial.print(i);
      }
    }
    delay(5000);
    for(int i=1200;i>=1182;i--)
    {
      for(int j=0;j<noofesc;j++)
      {
        Serial.print(" Decreasing PWM\n");
        Flame[j].write(i);
        delay(100);
        Serial.print(i);
      }
    }
  }
  if((analogRead(C_pin)>= 820)&&(count == 0))
  {
    count = 1;
    delay(800);
    for(int i=0;i<noofesc;i++)
    {
      Flame[i].write(1750);
      Serial.print("Max_PWM limit was set\n");
    }
    delay(3000);
    for(int i=0;i<noofesc;i++)
    {
      Flame[i].write(1160);
      Serial.print("Min_PWM limit was set\n");
    }
  }
  if(analogRead(C_pin)<=250)
  {
    count = 0;
//    for(int i=0;i<noofesc;i++)
//    {
//      Flame[i].write(1750);
//      //Serial.print("Max_PWM limit was set\n");
//    }
    //Serial.println("Set Count back to 0\n");    
  }
}
