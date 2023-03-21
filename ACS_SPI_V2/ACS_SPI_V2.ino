#include <SoftSPI.h>
#include <SPI.h>
#include <Wire.h>
#include<sys/types.h>
//#include<sys/stat.h>
#include <fcntl.h> 
//#include <serialprintf.h> 
#include <SoftWire.h>
//#include <printf.h>

SoftSPI ACSSPI(8, A4, A5);

#define kNOERROR 0
#define kREADERROR 1
#define kWRITEERROR 2

const uint32_t WRITE = 0x00;
const uint32_t READ = 0x80;
const uint32_t COMMAND_MASK = 0x80;
const uint32_t ADDRESS_MASK = 0x7F;

const uint16_t Chipselect = 9; // PB1

unsigned long nextTime;

void setup()
{
  ACSSPI.begin();
  Serial.begin(115200);

  ACSSPI.setClockDivider(SPI_CLOCK_DIV2);

  pinMode(Chipselect, OUTPUT);
  digitalWrite(Chipselect, HIGH);
  
  uint32_t unused;
  Read(0x0, unused);


  Write(0x5E, 0x4F70656E);   // Unlock device
  Write(0x60, 0x00000001);
  nextTime = millis();
}

void loop()
{
    uint32_t vrms;
    uint32_t irms;
    uint32_t pactive;
    uint32_t paparent;
    uint32_t pimag;
    uint32_t pfactor;
    uint32_t numptsout;
    uint32_t vrmsavgonesec;
    uint32_t irmsavgonesec;
    uint32_t vrmsavgonemin;
    uint32_t irmsavgonemin;
    uint32_t pactavgonesec;
    uint32_t pactavgonemin;
    uint32_t vcodes;
    uint32_t icodes;
    uint32_t pinstant;
    uint32_t flags;
  uint32_t v_i_v_rms_o;
  uint32_t v_pactive_o;
  uint32_t v_papparent_o;
  uint32_t v_numptsout_o;
  uint32_t v_vrmsavgs_o;
  uint32_t v_vrmsavgm_o;
  uint32_t v_pactavgs_o;
  uint32_t v_pactavgm_o;
  uint32_t v_vcodes_o;
  uint32_t v_pinstant_o;
  uint32_t v_dsp_status_o;
  uint32_t Settings;
  uint32_t Settings3;
  
  
    // Every 1/2 second, toggle the state of the LED and read the ACS37800
    if (nextTime < millis())
    { 
        Write(0x1C, 0x00021C00);
        Write(0x1E, 0x01081783);
        Read(0x41, v_i_v_rms_o);
        Read(0x21, v_pactive_o);
        Read(0x22, v_papparent_o);
        Read(0x25, v_numptsout_o);
        Read(0x26, v_vrmsavgs_o);
        Read(0x27, v_vrmsavgm_o);
        Read(0x28, v_pactavgs_o);
        Read(0x29, v_pactavgm_o);
        Read(0x2A, v_vcodes_o);
        Read(0x2C, v_pinstant_o);
        Read(0x2D, v_dsp_status_o);
        Read(0x1D, Settings);
        Read(0x1F, Settings3);

        uint32_t Settings1 = ( Settings & 0xFFFF);
        Serial.print("Settings1 =\r");
        Serial.print(Settings & 0xFFFF);
        Serial.print("\n");
        uint32_t Settings2 = ( Settings >> 16 & 0xFFFF);
        Serial.print("Settings2 =\r");
        Serial.print(Settings2);
        Serial.print("\n");
        uint32_t Settings4 = ( Settings3 & 0xFFFF);
        Serial.print("Settings4 =\r");
        Serial.print(Settings4);
        Serial.print("\n");
        uint32_t Settings5 = ( Settings3 >> 16 & 0xFFFF);
        Serial.print("Settings5 =\r");
        Serial.print(Settings5);
        Serial.print("\n");

        vrms = (v_i_v_rms_o & 0xFFFF);
        float vrms1 = ConvertUnsignedFixedPoint(vrms, 16, 16);
        Serial.print("vrms =\r");
        Serial.print(vrms1*59.91);
        Serial.print("\n");
        irms = (v_i_v_rms_o >> 16) & 0xFFFF;
        float irms1 = ConvertUnsignedFixedPoint(irms, 16, 16);
        Serial.print("irms =\r");
        Serial.print(irms1*100);
        Serial.print("\n");
//        Serial.printf("irms = %ul, %f\n", irms, ConvertUnsignedFixedPoint(irms, 16, 16));
        pactive = v_pactive_o & 0xFFFF;
        float pactive1 = ConvertUnsignedFixedPoint(pactive, 16, 16);
        Serial.print("pactive =\r");
        Serial.print(pactive1*59.91);
        Serial.print("\n");
//        Serial.printf("pactive = %dl, %f\n", pactive, ConvertSignedFixedPoint(pactive, 15, 16));
        pimag = (v_pactive_o >> 16) & 0xFFFF;
        float pimag1 = ConvertUnsignedFixedPoint(pimag, 16, 16);
        Serial.print("pimag =\r");
        Serial.print(pimag1*59.91);
        Serial.print("\n");
//        Serial.printf("pimag = %ul, %f\n", pimag, ConvertUnsignedFixedPoint(pimag, 16, 16));       
        paparent = v_papparent_o & 0xFFFF;
        float paparent1 = ConvertUnsignedFixedPoint(paparent, 16, 16);
        Serial.print("paparent =\r");
        Serial.print(paparent1*59.91);
        Serial.print("\n");
        //Serial.printf("paparent = %ul, %f\n", paparent, ConvertUnsignedFixedPoint(pactive, 15, 16));        
        pfactor = (v_papparent_o >> 16) & 0x7FF;
        float pfactor1 = ConvertUnsignedFixedPoint(pfactor, 16, 16);
        Serial.print("pfactor =\r");
        Serial.print(pfactor1);
        Serial.print("\n");
//        Serial.printf("pfactor = %dl, %f\n", pfactor, fabs(ConvertSignedFixedPoint(pfactor, 10, 11)));
        numptsout = v_numptsout_o & 0x3FF;   
        float numptsout1 = ConvertUnsignedFixedPoint(numptsout, 16, 16);
        Serial.print("numptsout =\r");
        Serial.print(numptsout1*1000);
        Serial.print("\n");   
//        Serial.printf("numptsout = %ul\n", numptsout);
        vrmsavgonesec = v_vrmsavgs_o & 0xFFFF;
        float vrmsavgonesec1 = ConvertUnsignedFixedPoint(vrmsavgonesec, 16, 16);
        Serial.print("vrmsavgonesec =\r");
        Serial.print(vrmsavgonesec1*59.91);
        Serial.print("\n");
//        Serial.printf("vrmsavgonesec = %ul, %f\n", vrmsavgonesec, ConvertUnsignedFixedPoint(vrmsavgonesec, 16, 16));
        irmsavgonesec = (v_vrmsavgs_o >> 16) & 0xFFFF;
        float irmsavgonesec1 = ConvertUnsignedFixedPoint(irmsavgonesec, 16, 16);
        Serial.print("irmsavgonesec =\r");
        Serial.print(irmsavgonesec*100);
        Serial.print("\n");
//        Serial.printf("irmsavgonesec = %ul, %f\n", irmsavgonesec, ConvertUnsignedFixedPoint(irmsavgonesec, 16, 16));
        vrmsavgonemin = v_vrmsavgm_o & 0xFFFF;
        float vrmsavgonemin1 = ConvertUnsignedFixedPoint(vrmsavgonemin, 16, 16);
        Serial.print("vrmsavgonemin =\r");
        Serial.print(vrmsavgonemin1*59.91);
        Serial.print("\n"); 
//        Serial.printf("vrmsavgonemin = %ul, %f\n", vrmsavgonemin, ConvertUnsignedFixedPoint(vrmsavgonemin, 16, 16));
        irmsavgonemin = (v_vrmsavgm_o >> 16) & 0xFFFF;
        float irmsavgonemin1 = ConvertUnsignedFixedPoint(irmsavgonemin, 16, 16);
        Serial.print("irmsavgonemin =\r");
        Serial.print(irmsavgonemin1);
        Serial.print("\n"); 
//        Serial.printf("irmsavgonemin = %ul, %f\n", irmsavgonemin, ConvertUnsignedFixedPoint(irmsavgonemin, 16, 16));
        pactavgonesec = v_pactavgs_o & 0xFFFF;
        float pactavgonesec1 = ConvertUnsignedFixedPoint(pactavgonesec, 16, 16);
        Serial.print("pactavgonesec =\r");
        Serial.print(pactavgonesec1*59.91);
        Serial.print("\n"); 
//        Serial.printf("pactavgonesec = %ul, %f\n", pactavgonesec, ConvertSignedFixedPoint(pactavgonesec, 15, 16));
        pactavgonemin = v_pactavgm_o & 0xFFFF;
        float pactavgonemin1 = ConvertUnsignedFixedPoint(pactavgonemin, 16, 16);
        Serial.print("pactavgonemin =\r");
        Serial.print("\n"); 
//        Serial.printf("pactavgonemin = %ul, %f\n", pactavgonemin, ConvertSignedFixedPoint(pactavgonemin, 15, 16));
        vcodes = v_vcodes_o & 0xFFFF;
        float vcodes1 = ConvertUnsignedFixedPoint(vcodes, 16, 16);
        Serial.print("vcodes =\r");
        Serial.print(vcodes1*1000);
        Serial.print("\n");
//        Serial.printf("vcodes = %ul, %f\n", vcodes, ConvertSignedFixedPoint(vcodes, 15, 16));
        icodes = (v_vcodes_o >> 16) & 0xFFFF;
        float icodes1 = ConvertUnsignedFixedPoint(icodes, 16, 16);
        Serial.print("icodes =\r");
        Serial.print(icodes1*1000);
        Serial.print("\n");
//        Serial.printf("icodes = %ul, %f\n", icodes, ConvertSignedFixedPoint(icodes, 15, 16));         
        pinstant = v_pinstant_o & 0xFFFF;
        float pinstant1 = ConvertUnsignedFixedPoint(pinstant, 16, 16);
        Serial.print("pinstant =\r");
        Serial.print(pinstant1*1000);
        Serial.print("\n");
//        Serial.printf("pinstant = %ul, %f\n", pinstant, ConvertSignedFixedPoint(pinstant, 15, 16));
//    
        Serial.print("pospf = ");
        Serial.println((v_papparent_o >> 28) & 0x1);
        Serial.print("posangle = ");
        Serial.println((v_papparent_o >> 27) & 0x1);
        
        Serial.print("undervoltage = ");
        Serial.println((v_dsp_status_o >> 4) & 0x1);
        Serial.print("overvoltage = ");
        Serial.println((v_dsp_status_o >> 3) & 0x1);
        Serial.print("faultlatched = ");
        Serial.println((v_dsp_status_o >> 2) & 0x1);
        Serial.print("faultout = ");
        Serial.println((v_dsp_status_o >> 1) & 0x1);
        Serial.print("vzerocrossout = ");
        Serial.println(v_dsp_status_o & 0x1);
        Serial.println();

        nextTime = millis() + 500L;
    }
}

uint16_t Read(uint8_t address, uint32_t& value)
{
    uint16_t results = kNOERROR;

    ACSSPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE3));

//    // Combine the register address and the command into one byte
//        uint8_t command = (address & ADDRESS_MASK) | READ;
        
        digitalWrite(Chipselect, LOW);
        
        ACSSPI.transfer(address);
        ACSSPI.transfer(0);
        ACSSPI.transfer(0);
        ACSSPI.transfer(0);
        ACSSPI.transfer(0);

        digitalWrite(Chipselect, HIGH);
        delayMicroseconds(10);
        digitalWrite(Chipselect, LOW);

        // send the command again to read the contents
        ACSSPI.transfer(address);
        value = (uint32_t)ACSSPI.transfer(0);
        value |= (uint32_t)ACSSPI.transfer(0) >> 8;
        value |= (uint32_t)ACSSPI.transfer(0) >> 16;
        value |= (uint32_t)ACSSPI.transfer(0) >> 24; // high byte

        digitalWrite(Chipselect, HIGH);

        ACSSPI.endTransaction();

    return results;
}

uint16_t Write(uint8_t address, uint32_t value)
{
    uint16_t results = kNOERROR;

     ACSSPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE3));

//        uint8_t command = ((address & ADDRESS_MASK) | WRITE);   

        digitalWrite(Chipselect, LOW);
        
        ACSSPI.transfer(address);
        ACSSPI.transfer((uint8_t)value);
        ACSSPI.transfer((uint8_t)(value << 8));
        ACSSPI.transfer((uint8_t)(value << 16));
        ACSSPI.transfer((uint8_t)(value << 24));

        digitalWrite(Chipselect, HIGH);

        ACSSPI.endTransaction();
        
      if (address < 0x10)
      {
          delay(30);  // If writing to EEPROM delay 30 ms
      }

    return results;
}

float ConvertUnsignedFixedPoint(uint32_t inputValue, uint16_t binaryPoint, uint16_t width)
{
    uint32_t mask;

    if (width == 32)
    {
        mask = 0xFFFFFFFF;
    }
    else
    {
        mask = (1UL << width) - 1UL;
    }

    return (float)(inputValue & mask) / (float)(1L << binaryPoint);
}

float ConvertSignedFixedPoint(uint32_t inputValue, uint16_t binaryPoint, uint16_t width)
{
    int32_t signedValue = SignExtendBitfield(inputValue, width);
    return (float)signedValue / (float)(1L << binaryPoint);
}

int32_t SignExtendBitfield(uint32_t data, uint16_t width)
{
  // If the bitfield is the width of the variable, don't bother trying to sign extend (it already is)
    if (width == 32)
    {
        return (int32_t)data;
    }

    int32_t x = (int32_t)data;
    int32_t mask = 1L << (width - 1);

    x = x & ((1 << width) - 1); // make sure the upper bits are zero

    return (int32_t)((x ^ mask) - mask);
}
