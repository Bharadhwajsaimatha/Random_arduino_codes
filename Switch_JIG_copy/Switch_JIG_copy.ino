
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

#define LSW_C_pin  12        /* Left side wing                 */
#define RSW_C_pin  13        /* Right side wing                */
#define LR_C_pin   4        /* Left Rudder                    */
#define RR_C_pin   44        /* Right Rudder                   */
#define LVA_C_pin1 6        /* Left VTOL arm Motor 1          */
#define LVA_C_pin2 7        /* Left VTOL arm Motor 2          */
#define RVA_C_pin1 8        /* Right VTOL arm Motor 1         */
#define RVA_C_pin2 9        /* Right VTOL arm Motor 2         */
#define LVA_LR_pin 10       /* Left Rudder signal through LVA */
#define RVA_RR_pin 11       /* Right Rudder signal through RVA*/

/* Defining Temperature Sensor pins */

#define ONE_WIRE_BUS_1 48   /* Left Side wing temp sensor          */
#define ONE_WIRE_BUS_2 49   /* Right Side wing temp sensor         */
#define ONE_WIRE_BUS_3 50   /* Left Rudder temp sensor             */
#define ONE_WIRE_BUS_4 51   /* Right Rudder temp sensor            */
#define ONE_WIRE_BUS_5 52   /* Left VTOL arm Motor 1 temp sensor   */
//#define ONE_WIRE_BUS_6 51   /* Left VTOL arm Motor 2 temp sensor   */
#define ONE_WIRE_BUS_7 53   /* Right VTOL arm Motor 1 temp sensor  */
//#define ONE_WIRE_BUS_8 53   /* Right VTOL arm Motor 2 temp sensor   */

/* Creating Objects for each */

Servo LSW;
Servo RSW;
Servo LR;
Servo RR;
Servo LVAM0;
Servo LVAM1;
Servo LVAM2;
Servo RVAM0;
Servo RVAM1;
Servo RVAM2;
TinyGPSPlus GPS_LW;
TinyGPSPlus GPS_RW;

/* Creating objects for Onewire(temperature sensors) */

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);
OneWire oneWire3(ONE_WIRE_BUS_3);
OneWire oneWire4(ONE_WIRE_BUS_4);
OneWire oneWire5(ONE_WIRE_BUS_5);
//OneWire oneWire6(ONE_WIRE_BUS_6);
OneWire oneWire7(ONE_WIRE_BUS_7);
//OneWire oneWire8(ONE_WIRE_BUS_8);

DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);
DallasTemperature sensors3(&oneWire3);
DallasTemperature sensors4(&oneWire4);
DallasTemperature sensors5(&oneWire5);
//DallasTemperature sensors6(&oneWire6);
DallasTemperature sensors7(&oneWire7);
//DallasTemperature sensors8(&oneWire8);

/* Private variables */

int angle = 0;
int i = 0, j , k ;
float T_LSW, T_RSW, T_RR, T_LR, T_LVA1, T_LVA2, T_RVA1, T_RVA2;

void setup()
{
  Serial.begin(9600);
  
  Serial1.begin(38400);     // For GPS Testing on LW :: Connect Rx on 18 and Tx on 19
  Serial2.begin(38400);     // For GPS Testing on RW :: Connect Rx on 17 and Tx on 16
 

  pinMode( LSW_S_pin , INPUT_PULLUP);
  pinMode( RSW_S_pin , INPUT_PULLUP);
  pinMode( LR_S_pin ,  INPUT_PULLUP);
  pinMode( RR_S_pin ,  INPUT_PULLUP);
  pinMode( LVA_S_pin , INPUT_PULLUP);
  pinMode( RVA_S_pin , INPUT_PULLUP);

  LSW.attach(LSW_C_pin);
  RSW.attach(RSW_C_pin);
  LR.attach(LR_C_pin);
  RR.attach(RR_C_pin);
  LVAM0.attach(LVA_LR_pin);
  LVAM1.attach(LVA_C_pin1, 1000 , 2000);
  LVAM2.attach(LVA_C_pin2, 1000 , 2000);
  RVAM0.attach(RVA_RR_pin);
  RVAM1.attach(RVA_C_pin1, 1000 , 2000);
  RVAM2.attach(RVA_C_pin2, 1000 , 2000);

}

/* Function to check the working of servo motors */

void ServoCheck(Servo Check1)
{
  Servo check = Check1;
  for (j = 0; j < 3 ; j++)
  {
    check.write(90);
    delay(500);
    check.write(140);
    delay(500);
    check.write(90);
    delay(500);
    check.write(40);
    delay(500);
  }
    // Sweep from 0 to 180 degrees:
    for (angle = 40; angle <= 140; angle += 5)
    {
      check.write(angle);
      delay(50);
    }
    //delay(2000);
    // And back from 180 to 0 degrees:
    for (angle = 140; angle >= 40; angle -= 5)
    {
      check.write(angle);
      delay(50);
    }
    check.write(90);
    delay(1000);
  
}

/* Function to check the working of BLDC motors */

void MotorCheck(Servo Motor)
{
  Servo ESC = Motor;
  ESC.write(1000); //Motor Initialisation
  delay(1000);
  ESC.write(1200);
  delay(3000);
  ESC.write(1000);
  delay(1000);
}

void GPSCheck(TinyGPSPlus checkGPS, int m)
{
  Serial.println("\t Entered GPS check");
  TinyGPSPlus gps = checkGPS;
  k = m;
  if(k == 1)
  {
  while (Serial1.available() > 0)
  {
  //Serial.println("\t Entered Serial 01");
  if (gps.encode(Serial1.read()))
  {
  Serial.println(F("\t No of Satellites = ")); 
  Serial.print(gps.satellites.value());
  Serial.println("");
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
  }
  Serial.println();
  if (millis() > 20000 && gps.charsProcessed() < 10)
  {
    Serial.print(F("\t No GPS detected: check wiring..."));
    //while (true);
  }
  }
  }
  if(k == 2)
  {
  while (Serial2.available() > 0)
  {
  Serial.println("Entered Serial 02");
  if (gps.encode(Serial2.read()))
  {
  Serial.println(F("\t No of Satellites = ")); 
  Serial.print(gps.satellites.value());
  Serial.println("");
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
  }
  Serial.println();
  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("\t No GPS detected: check wiring..."));
    //while (true);
  }
  }
  }
}

void TempsensorBegin()
{
  sensors1.begin();
  sensors2.begin();
  sensors3.begin();
  sensors4.begin();
  sensors5.begin();
 // sensors6.begin();
  sensors7.begin();
 // sensors8.begin();
}

void loop()
{
    TempsensorBegin();
    sensors1.requestTemperatures();
    sensors2.requestTemperatures();
    sensors3.requestTemperatures();
    sensors4.requestTemperatures();
    sensors5.requestTemperatures();
   // sensors6.requestTemperatures();
    sensors7.requestTemperatures();
   // sensors8.requestTemperatures();
    
  while(1)
  {
  if (digitalRead(LSW_S_pin) == 0)
  {
    Serial.println("");
    Serial.println("\t Checking Left Side Wing...");
    ServoCheck(LSW);
    Serial.println("\t Checking for GPS ");
    GPSCheck(GPS_LW , 1);
    Serial.println("");
    Serial.println("\t GPS check Completed");
    T_LSW = sensors1.getTempCByIndex(0);
    Serial.print("\t Temperature LSW : ");
    Serial.print(T_LSW);
    Serial.println("");
    Serial.println("\t Left Side Wing Check completed.");
  }
  if (digitalRead(RSW_S_pin) == 0)
  {
    Serial.println("");
    Serial.println("\t Checking Right Side Wing...");
    ServoCheck(RSW);
    Serial.println("\t Checking for GPS ");
    GPSCheck(GPS_RW , 2);
    Serial.println("");
    Serial.println("\t GPS check Completed");
    T_RSW = sensors2.getTempCByIndex(0);
    Serial.print("\t Temperature RSW : ");
    Serial.print(T_RSW);
    Serial.println("");
    Serial.println("\t Right Side Wing Check completed.");
  }
  if (digitalRead(LR_S_pin) == 0)
  {
    Serial.println("");
    Serial.println("\t Checking Left Rudder...");
    ServoCheck(LR);
    T_LR = sensors3.getTempCByIndex(0);
    Serial.print("\t Temperature LR : ");
    Serial.print(T_LR);
    Serial.println("");
    Serial.println("\t Left Rudder Check completed.");
  }
  if (digitalRead(RR_S_pin) == 0)
  {
    Serial.println("");
    Serial.println("\t Checking Right Rudder...");
    ServoCheck(RR);
    T_RR = sensors4.getTempCByIndex(0);
    Serial.print("\t Temperature RR : ");
    Serial.print(T_RR);
    Serial.println("");
    Serial.println("\t Right Rudder Check completed.");
  }
  if (digitalRead(LVA_S_pin) == 0)
  {
    Serial.println("");
    Serial.println("\t Checking Left VTOL arm...");
    Serial.println("\t Checking Motor 1");
    MotorCheck(LVAM1);
    T_LVA1 = sensors5.getTempCByIndex(0);
    Serial.print("\t Temperature LVA1 : ");
    Serial.print(T_LVA1);
    Serial.println("");
    Serial.println("\t Checking Motor 2");
    MotorCheck(LVAM2);
    T_LVA2 = sensors5.getTempCByIndex(1);
    Serial.print("\t Temperature LVA2 : ");
    Serial.print(T_LVA2);
    Serial.println("");
    Serial.println("\t Checking Left Rudder through LVA...");
    ServoCheck(LVAM0);
    Serial.println("\t Left Rudder Check completed.");
    Serial.println("\t Left VTOL arm Check completed.");
  }
  if (digitalRead(RVA_S_pin) == 0)
  {
    Serial.println("");
    Serial.println("\t Checking Right VTOL arm...");
    Serial.println("\t Checking Motor 1");
    MotorCheck(RVAM1);
    T_RVA1 = sensors7.getTempCByIndex(0);
    Serial.print("\t Temperature RVA1 : ");
    Serial.print(T_RVA1);
    Serial.println("");
    Serial.println("\t Checking Motor 2");
    MotorCheck(RVAM2);
    T_RVA2 = sensors7.getTempCByIndex(1);
    Serial.print("\t Temperature RVA2 : ");
    Serial.print(T_RVA2);
    Serial.println("");
    Serial.println("\t Checking Right Rudder through RVA...");
    ServoCheck(RVAM0);
    Serial.println("\t Right Rudder Check completed.");
    Serial.println("\t Right VTOL arm Check completed.");
  }
  else
  {
    Serial.println("");
    Serial.println("\t Nothing is turned ON");
  }
  delay(250);
  }
}
