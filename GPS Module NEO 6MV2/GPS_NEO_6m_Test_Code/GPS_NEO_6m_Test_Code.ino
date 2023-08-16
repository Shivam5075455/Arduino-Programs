#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Pin define for GPS Module
const int GPS_TX = 8;
const int GPS_RX = 9;

SoftwareSerial myGPS(GPS_TX, GPS_RX);
TinyGPSPlus gps;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myGPS.begin(9600); // initiate GPS serial communication

}

void loop() {
  // put your main code here, to run repeatedly:

  while(myGPS.available()>0){
    if(gps.encode(myGPS.read())){
      if(gps.location.isValid()){

//        latitude = gps.location.lat();
//        longitude = gps.location.lng();

        Serial.print("Latitiude: ");
        Serial.print(gps.location.lat(), 6);
        Serial.print(", Longitude: ");
        Serial.print(gps.location.lng(), 6);
        Serial.println("");
      }
    }
  }

}
