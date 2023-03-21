#include <OneWireHub.h>
#include <DallasTemperature.h>

//int pinToToggle = 13;

#define ONE_WIRE_BUS_1    2         //ESC                     D2
#define ONE_WIRE_BUS_2    3         //Motor                   D3
//#define ONE_WIRE_BUS_3    2       //ESC3                  A2
//#define ONE_WIRE_BUS_4    3       //ESC4                  A3
//#define ONE_WIRE_BUS_5    4       //MOTOR1                A4
//#define ONE_WIRE_BUS_6    5       //MOTOR2                A5
//#define ONE_WIRE_BUS_7    6       //MOTOR3                A6
//#define ONE_WIRE_BUS_8    7       //MOTOR4                A7
//#define ONE_WIRE_BUS_9    11      //FIXED_WING_MOTOR      A11

float t1, t2, t3, t4, t5, t6, t7, t8, t9;

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);
//OneWire oneWire3(ONE_WIRE_BUS_3);
//OneWire oneWire4(ONE_WIRE_BUS_4);
//OneWire oneWire5(ONE_WIRE_BUS_5);
//OneWire oneWire6(ONE_WIRE_BUS_6);
//OneWire oneWire7(ONE_WIRE_BUS_7);
//OneWire oneWire8(ONE_WIRE_BUS_8);
//OneWire oneWire9(ONE_WIRE_BUS_9);

DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);
//DallasTemperature sensors3(&oneWire3);
//DallasTemperature sensors4(&oneWire4);
//DallasTemperature sensors5(&oneWire5);
//DallasTemperature sensors6(&oneWire6);
//DallasTemperature sensors7(&oneWire7);
//DallasTemperature sensors8(&oneWire8);
//DallasTemperature sensors9(&oneWire9);

void setup(void)
{
  Serial.begin(9600);
  
  sensors1.begin();
  sensors2.begin();
//  sensors3.begin();
//  sensors4.begin();
//  sensors5.begin();
//  sensors6.begin();
//  sensors7.begin();
//  sensors8.begin();
//  sensors9.begin();

//  pinMode(PC13, OUTPUT);
}
 
 
void loop(void)
{ 
  sensors1.requestTemperatures();
  sensors2.requestTemperatures();
//  sensors3.requestTemperatures();
//  sensors4.requestTemperatures();
//  sensors5.requestTemperatures();
//  sensors6.requestTemperatures();
//  sensors7.requestTemperatures();
//  sensors8.requestTemperatures();
//  sensors9.requestTemperatures();

  // digitalWrite(PC13, HIGH);
  
  t1 = sensors1.getTempCByIndex(0);
//  Serial.print("Temperature ESC : \t");
  Serial.print(t1);
  //Serial.print((char)176);
//  Serial.print(" C");
  Serial.print(",");
//  Serial.print("\t || \t");
//  
//  t2 = sensors2.getTempCByIndex(0);
////  Serial.print("Temperature Motor : \t");
//  Serial.print(t2);
//  Serial.print("\n");
//  
//  t3 = sensors3.getTempCByIndex(0);
//  Serial.print(t3);
//  Serial.print(",");
//  
//  t4 = sensors4.getTempCByIndex(0);
//  Serial.print(t4);
//  Serial.print(",");
//  
//  t5 = sensors5.getTempCByIndex(0);
//  Serial.print(t5);
//  Serial.print(",");
//  
//  t6 = sensors6.getTempCByIndex(0);
//  Serial.print(t6);
//  Serial.print(",");
//  
//  t7 = sensors7.getTempCByIndex(0);
//  Serial.print(t7);
//  Serial.print(",");
//  
//  t8 = sensors8.getTempCByIndex(0);
//  Serial.print(t8);
//  Serial.print(",");
//  
//  t9 = sensors9.getTempCByIndex(0);
//  Serial.print(t9);
  
  Serial.print("\n\r");
  delay(500);

//  digitalWrite(PC13, LOW);
//  delay(500);
}
