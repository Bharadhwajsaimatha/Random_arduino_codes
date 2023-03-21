/* SWITCH JIG code */

#include <Servo.h>
#include <TinyGPS++.h>
#include <OneWire.h>
#include <DallasTemperature.h>


/* Defining the Digital pins for the Switches */

#define LSW_S_pin  22  /* Left side wing control switch  */
#define RSW_S_pin  23  /* Right side wing control switch */
#define LR_S_pin   24  /* Left Rudder control switch     */
#define RR_S_pin   25  /* Right Rudder control switch    */
#define LVA_S_pin  26  /* Left VTOL arm control switch   */
#define RVA_S_pin  27  /* Right VTOL arm control switch  */

/* Defining the signal pins of the motors */

#define LSW_C_pin  2        /* Left side wing                 */
#define RSW_C_pin  3        /* Right side wing                */
#define LR_C_pin   4        /* Left Rudder                    */
#define RR_C_pin   5        /* Right Rudder                   */
#define LVA_C_pin1 6        /* Left VTOL arm Motor 1          */
#define LVA_C_pin2 7        /* Left VTOL arm Motor 2          */
#define RVA_C_pin1 8        /* Right VTOL arm Motor 1         */
#define RVA_C_pin2 9        /* Right VTOL arm Motor 2         */
#define LVA_LR_pin 10       /* Left Rudder signal through LVA */
#define RVA_RR_pin 11       /* Right Rudder signal through RVA*/

/* Private variables */

//int angle = 0;
int i = 0, j ;

/* Creating classes for servo and motor check */

class ServoMotor
{
  Servo servo;                     // the servo
  int k ;
  int angle;                       // current servo angleition 
  int increment;                   // increment to move for each interval
  int  updateInterval_1 = 200;        // interval between updates
  int  updateInterval_2 = 1000;
  int  updateInterval_3 = 2000;
  int  updateInterval_4 = 3000;
  int  updateInterval_5 = 4000;
  unsigned long lastUpdate_1 = 0;        // last update of angleition
  unsigned long lastUpdate_2 = 0;
  unsigned long lastUpdate_3 = 0;
  unsigned long lastUpdate_4 = 0;
  unsigned long lastUpdate_5 = 0;
  
public: 
  ServoMotor()
  {
    //increment = 5;
  }
  
  void Attach(int pin)
  {
    servo.attach(pin);
  }
  
  void Detach()
  {
    servo.detach();
  }
  
  void Update()
  {
   // k = 1;
    for(j = 0 ; j < 3 ; j++)
    {
    int L=0;
    switch(L)
    {
      case 0 :
      if((millis() - lastUpdate_2) > updateInterval_2)  // time to update
      {
        lastUpdate_2 = millis(); 
        //angle += increment;
        servo.write(90);
        Serial.println("90 done");
        L=1;
      }
      break;

      case 1:
      if((millis() - lastUpdate_2) > updateInterval_2)  // time to update
      {
        lastUpdate_2 = millis(); 
        //angle += increment;
        servo.write(140);
        Serial.println("140 done");
        L=2;
      }
      break;

      case 2:
      if((millis() - lastUpdate_2) > updateInterval_2)  // time to update
      {
        lastUpdate_2 = millis(); 
        //angle += increment;
        servo.write(90);
        Serial.println("90 done");
        L = 3;
      }
      
      break;

      case 3:
      if((millis() - lastUpdate_2) > updateInterval_2)  // time to update
      {
        lastUpdate_2 = millis(); 
        //angle += increment;
        servo.write(40);
        Serial.println("40 done");
        L=0;
      }
      
      break;
    }
//    if((millis() - lastUpdate_2) > updateInterval_2)  // time to update
//      {
//        lastUpdate_2 = millis(); 
//        //angle += increment;
//        servo.write(90);
//        Serial.println("90 done");
//      }
//    if((millis() - lastUpdate_3) > updateInterval_3)  // time to update
//      {
//        lastUpdate_3 = millis(); 
//        //angle += increment;
//        servo.write(140);
//        Serial.println("140 done");
//      } 
//    if((millis() - lastUpdate_4) > updateInterval_4)  // time to update
//      {
//        lastUpdate_4 = millis(); 
//        //angle += increment;
//        servo.write(90);
//        Serial.println("90 done");
//      } 
//    if((millis() - lastUpdate_5) > updateInterval_5)  // time to update
//      {
//        lastUpdate_5 = millis(); 
//        //angle += increment;
//        servo.write(40);
//        Serial.println("40 done");
//      }
   // }
    }
//    k = 2;
//    if(k == 2)
//    {
    for (angle = 40; angle <= 140;)// angle += 5)
    {
      if((millis() - lastUpdate_1) > updateInterval_1)  // time to update
      {
        lastUpdate_1 = millis(); 
        angle += 5;
        servo.write(angle);
        //Serial.println(angle);
        if ((angle >= 180) || (angle <= 0)) // end of sweep
        {
          // reverse direction
          increment = -increment;
        }
      }
    }
    Serial.println("Ramping up done");
    for (angle = 140; angle >= 40;)// angle -= 5)
    {
      if((millis() - lastUpdate_1) > updateInterval_1)  // time to update
      {
        lastUpdate_1 = millis(); 
        angle -= 5;
        servo.write(angle);
        //Serial.println(angle);
        if ((angle >= 180) || (angle <= 0)) // end of sweep
        {
          // reverse direction
          increment = -increment;
        }
      }
    }
    Serial.println("Ramping down done");
   // }
  }
};

ServoMotor LSW;
ServoMotor RSW;
ServoMotor LR;
ServoMotor RR;
TinyGPSPlus GPS_LW;
TinyGPSPlus GPS_RW;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(115200);     // For GPS Testing on LW :: Connect Rx on 18 and Tx on 19
  Serial2.begin(115200);     // For GPS Testing on RW :: Connect Rx on 17 and Tx on 16

  pinMode( LSW_S_pin , INPUT_PULLUP);
  pinMode( RSW_S_pin , INPUT_PULLUP);
  pinMode( LR_S_pin ,  INPUT_PULLUP);
  pinMode( RR_S_pin ,  INPUT_PULLUP);
  pinMode( LVA_S_pin , INPUT_PULLUP);
  pinMode( RVA_S_pin , INPUT_PULLUP);

  LSW.Attach(LSW_C_pin);
  RSW.Attach(RSW_C_pin);
  LR.Attach(LR_C_pin);
  RR.Attach(RR_C_pin);

}

void GPSCheck(TinyGPSPlus checkGPS, int m)
{
  TinyGPSPlus gps = checkGPS;
  int n;
  n = m;
  if(n == 1)
  {
  while (Serial1.available() > 0)
  if (gps.encode(Serial1.read()))
  Serial.print(F("\t Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("\t INVALID \n"));
  }

  Serial.println();
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.print(F("\t No GPS detected: check wiring..."));
    //while (true);
  }
  }
   if(n == 2)
  {
  while (Serial2.available() > 0)
  if (gps.encode(Serial2.read()))
  Serial.print(F("\t Location: "));
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.print(F("\t INVALID"));
  }

  Serial.println();
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("\t No GPS detected: check wiring..."));
    //while (true);
  }
  }
}

void loop()
{
  while(1)
  {
  if (digitalRead(LSW_S_pin) == 0)
  {
    Serial.println("");
    Serial.println("\t Checking Left Side Wing...");
    //ServoCheck(LSW);
    LSW.Update();
    Serial.println("\t Left Side Wing Check completed.");
    Serial.println("\t Checking for GPS ");
    GPSCheck(GPS_LW , 1);
    Serial.println("\t GPS check Completed");
  }
  if (digitalRead(RSW_S_pin) == 0)
  {
    Serial.println("");
    Serial.println("\t Checking Right Side Wing...");
//    ServoCheck(RSW);
    RSW.Update();
    Serial.println("\t Right Side Wing Check completed.");
    Serial.println("\t Checking for GPS ");
    GPSCheck(GPS_RW , 2);
    Serial.println("\t GPS check Completed");
  }
  if (digitalRead(LR_S_pin) == 0)
  {
//    Serial.println("");
//    Serial.println("\t Checking Left Rudder...");
//    ServoCheck(LR);
    LR.Update();
//    Serial.println("\t Left Rudder Check completed.");
  }
  if (digitalRead(RR_S_pin) == 0)
  {
//    Serial.println("");
//    Serial.println("\t Checking Right Rudder...");
//    ServoCheck(RR);
    RR.Update();
//    Serial.println("\t Right Rudder Check completed.");
  }
//  if (digitalRead(LVA_S_pin) == 0)
//  {
//    Serial.println("");
//    Serial.println("\t Checking Left VTOL arm...");
//    Serial.println("\t Checking Motor 1");
//    MotorCheck(LVAM1);
//    Serial.println("\t Checking Motor 2");
//    MotorCheck(LVAM2);
////    Serial.println("\t Checking Left Rudder through LVA...");
////    ServoCheck(LVAM0);
////    Serial.println("\t Left Rudder Check completed.");
//    Serial.println("\t Left VTOL arm Check completed.");
//  }
//  if (digitalRead(RVA_S_pin) == 0)
//  {
//    Serial.println("");
//    Serial.println("\t Checking Right VTOL arm...");
//    Serial.println("\t Checking Motor 1");
//    MotorCheck(RVAM1);
//    Serial.println("\t Checking Motor 2");
//    MotorCheck(RVAM2);
////    Serial.println("\t Checking Right Rudder through RVA...");
////    ServoCheck(RVAM0);
////    Serial.println("\t Right Rudder Check completed.");
//    Serial.println("\t Right VTOL arm Check completed.");
//  }
//  else
//  {
//    Serial.println("");
//    Serial.println("\t Nothing is turned ON");
//  }
//  }
}
}
