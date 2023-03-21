// 08/10/2021. Test code for Aniruddha's test                                                                   
#include <Servo.h>

#define no_servo  5
#define period 1000

Servo test[no_servo];

int servo_pins[no_servo] = {5,6,9,10,11};
int count = 0;
unsigned long timer = 0;

void setup()
{
  
  Serial.begin(9600);
  for(int i=0; i<no_servo; i++)
  {
    test[i].attach(servo_pins[i]);
    test[i].write(45);
  } 
  delay(100);  
}

void loop() 
{
  timer = millis();
  if(count>=0 && count<100)
  {
  for (int angle = 45; angle <= 135; angle += 5)
  { 
      for(int j = 0; j < no_servo; j++)
      {
        test[j].write(angle);  
        delay(15);    
      }
  }                      
  for (int angle = 135; angle >= 45; angle -= 5)
  { 
 
    for(int j = 0; j < no_servo; j++)
    {
      test[j].write(angle);  
      delay(15);    
    } 
  }
  }
  else if(count>=100 && count<600)
  { 
    for(int i=0; i<no_servo; i++)
    {
      test[i].write(90);
    } 
  } 
  else
  {
    count = 0;
  }
  while(millis()<= timer + period)
  {
    //Serial.print(timer);
    
    //do nothing
  }
  count++;
  
}
