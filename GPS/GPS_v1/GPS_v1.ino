#include <TinyGPS++.h>
//#include <SoftwareSerial.h>

//static const int RXPin = 4, TXPin = 3;
//static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
//SoftwareSerial ss(RXPin, TXPin);

void setup(){
  Serial.begin(9600);
  Serial1.begin(38400);
  //ss.begin(GPSBaud);
}

void loop(){
  // This sketch displays information every time a new sentence is correctly encoded.
  while (Serial1.available() > 0){
    Serial.println(" serial available");
    gps.encode(Serial1.read());
    Serial.println("read done");
    if (gps.location.isUpdated()){
      Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
    }
  }
  Serial.println("Nothing Detected");
}
