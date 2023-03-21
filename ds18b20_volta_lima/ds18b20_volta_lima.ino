/*
 * Author: Prathamesh C.
 * Reading single byte data
 * Reading byte stream
 * Using two UARTs at the same time, one for printing and for reading.
 * https://github.com/stm32duino/BoardManagerFiles/raw/master/package_stmicroelectronics_index.json
*/

#include <OneWire.h>                  //Jim Studt
#include <DallasTemperature.h>        //Miles Burton

#define MAX_LENGTH        27
#define BYTE_STREAM       1
#define BYTE_ONLY         0

#define ONE_WIRE_BUS_1    0       //ESC1                  A0
#define ONE_WIRE_BUS_2    1       //ESC2                  A1
#define ONE_WIRE_BUS_3    2       //ESC3                  A2
#define ONE_WIRE_BUS_4    3       //ESC4                  A3
#define ONE_WIRE_BUS_5    4       //MOTOR1                A4
#define ONE_WIRE_BUS_6    5       //MOTOR2                A5
#define ONE_WIRE_BUS_7    6       //MOTOR3                A6
#define ONE_WIRE_BUS_8    7       //MOTOR4                A7
#define ONE_WIRE_BUS_9    11      //FIXED_WING_MOTOR      A11

float t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15, t16;

char rxBuffer[MAX_LENGTH];
char byteData;

int8_t numOfBytes=0;

int8_t startRxFrame=0, stopRxFrame=0, firstA=0, firstB=0, i=0;

int32_t cellVol1=0, cellVol2=0, cellVol3=0, cellVol4=0, cellVol5=0, cellVol6=0, cellVol7=0, cellVol8=0, batV=0, current=0, temp=0, soc=0, rem=0;
float fc1, fc2, fc3, fc4, fc5, fc6, fc7, fc8, batVF, currentF, tempF, socF, remF;

OneWire oneWire1(ONE_WIRE_BUS_1);
OneWire oneWire2(ONE_WIRE_BUS_2);

DallasTemperature sensors1(&oneWire1);
DallasTemperature sensors2(&oneWire2);

void setup(void)
{
  Serial.begin(115200);
  Serial2.begin(115200);
  Serial3.begin(115200);
  sensors1.begin();
  sensors2.begin();
}
 
void loop(void)
{
  sensors1.requestTemperatures();
  sensors2.requestTemperatures();
  
  t1 = sensors1.getTempCByIndex(0);
  t2 = sensors1.getTempCByIndex(1);
  t3 = sensors1.getTempCByIndex(2);
  t4 = sensors1.getTempCByIndex(3);
  t5 = sensors1.getTempCByIndex(4);
  t6 = sensors1.getTempCByIndex(5);
  t7 = sensors1.getTempCByIndex(6);
  t8 = sensors1.getTempCByIndex(7);

  t9 = sensors2.getTempCByIndex(0);
  t10 = sensors2.getTempCByIndex(1);
  t11 = sensors2.getTempCByIndex(2);
  t12 = sensors2.getTempCByIndex(3);
  t13 = sensors2.getTempCByIndex(4);
  t14 = sensors2.getTempCByIndex(5);
  t15 = sensors2.getTempCByIndex(6);
  t16 = sensors2.getTempCByIndex(7);

  #if BYTE_ONLY
    if(Serial2.available())
    {
      char byteData = Serial2.read();
      Serial2.write(byteData);
    }
  #endif

  #if BYTE_STREAM 
    while(Serial2.available()!=0)
    {
      byteData = Serial2.read();
      if(byteData == 0xAA && firstA == 0)
      {
        firstA = 1;
      }
      
      if(byteData == 0xAA && firstA == 1)
      {
        startRxFrame = 1;
      }
      else
      {
        firstA = 0;
      }
      
      if(startRxFrame == 1)
      {
        rxBuffer[i] = byteData;
        i++;
      }
      
      if(byteData == 0xBB && firstB == 0)
      {
        firstB = 1;
      }
      
      if(firstB == 1 &&  byteData == 0xBB)
      {
        startRxFrame = 0;
        stopRxFrame = 1;
        i=0;  //Reset the buffer index to 0
      }
      
      if(stopRxFrame == 1 && startRxFrame == 0)
      {        
        cellVol1 = rxBuffer[3]<<8;
        cellVol1 = cellVol1 + rxBuffer[4];

        cellVol2 = rxBuffer[5]<<8;
        cellVol2 = cellVol2 + rxBuffer[6];

        cellVol3 = rxBuffer[7]<<8;
        cellVol3 = cellVol3 + rxBuffer[8];

        cellVol4 = rxBuffer[9]<<8;
        cellVol4 = cellVol4 + rxBuffer[10];

        cellVol5 = rxBuffer[11]<<8;
        cellVol5 = cellVol5 + rxBuffer[12];

        cellVol6 = rxBuffer[13]<<8;
        cellVol6 = cellVol6 + rxBuffer[14];

        cellVol7 = rxBuffer[15]<<8;
        cellVol7 = cellVol7 + rxBuffer[16];
        
        cellVol8 = rxBuffer[17]<<8;
        cellVol8 = cellVol8 + rxBuffer[18];

        batV = rxBuffer[19]<<8;
        batV = batV + rxBuffer[20];

        current = rxBuffer[21]<<8;
        current = current + rxBuffer[22];

        temp = rxBuffer[23];

        soc = rxBuffer[24];

        rem = rxBuffer[25];

        fc1 = (cellVol1*1.0)/1000;
        fc2 = (cellVol2*1.0)/1000;
        fc3 = (cellVol3*1.0)/1000;
        fc4 = (cellVol4*1.0)/1000;
        fc5 = (cellVol5*1.0)/1000;
        fc6 = (cellVol6*1.0)/1000;
        fc7 = (cellVol7*1.0)/1000;
        fc8 = (cellVol8*1.0)/1000;
        batVF = (batV*1.0)/1000;
        currentF = (current*1.0)/1000;
        tempF = (temp*1.0)/1000;
        socF = (soc*1.0)/1000;
        remF = (rem*1.0)/1000;

        Serial3.print(fc1);
        Serial3.print(", ");
        Serial3.print(fc2);
        Serial3.print(", ");
        Serial3.print(fc3);
        Serial3.print(", ");
        Serial3.print(fc4);
        Serial3.print(", ");
        Serial3.print(fc5);
        Serial3.print(", ");
        Serial3.print(fc6);
        Serial3.print(", ");
        Serial3.print(fc7);
        Serial3.print(", ");
        Serial3.print(fc8);
        Serial3.print(", ");
        Serial3.print(batVF);
        Serial3.print(", ");
        Serial3.print(currentF);
        Serial3.print(", ");
        Serial3.print(tempF);
        Serial3.print(", ");
        Serial3.print(socF);
        Serial3.print(", ");
        Serial3.print(remF);
        Serial3.print(", ");
        Serial3.print(t1);
        Serial3.print(", ");
        Serial3.print(t2);
        Serial3.print(", ");
        Serial3.print(t3);
        Serial3.print(", ");
        Serial3.print(t4);
        Serial3.print(", ");
//        Serial3.print(t5);
//        Serial3.print(", ");
//        Serial3.print(t6);
//        Serial3.print(", ");
//        Serial3.print(t7);
//        Serial3.print(", ");
        Serial3.print(t9);
        Serial3.print(", ");
        Serial3.print(t10);
        Serial3.print(", ");
        Serial3.print(t11);
        Serial3.print(", ");
        Serial3.print(t12);
//        Serial3.print(", ");
//        Serial3.print(t12);
//        Serial3.print(", ");
//        Serial3.print(t13);
//        Serial3.print(", ");
//        Serial3.print(t14);
//        Serial3.print(", ");
//        Serial3.print(t15);
//        Serial3.print(", ");
//        Serial3.print(i);
        Serial3.println("");
        delay(1000);
      }
    }
  #endif
}
