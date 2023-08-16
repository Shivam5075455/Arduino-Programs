// Library for GPS Module 
#include <SoftwareSerial.h>
#include <TinyGPS++.h>

// Library for LoRa
 #include<LoRa.h>
 
// Pin define for LoRa
 #define SS 15 // ss -> chip select pin
 #define RST 16 // reset pin
 #define DIO0 2 // thi is an interrupt pin
 
// Library for 1.3 inch OLED display
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

//define OLED address and size
#define Address 0x3C
#define height 64
#define width 128
#define reset -1
// Pin define for GPS Module
const int GPS_TX = D3;
const int GPS_RX = D4;
// 
//double lati, longi;
SoftwareSerial myGPS(GPS_TX, GPS_RX);
TinyGPSPlus gps;

//pass above parameters
Adafruit_SH1106G display = Adafruit_SH1106G(width, height, &Wire, reset);

double latitude = 0.0, longitude = 0.0;

void setup() {
  Serial.begin(9600);
  myGPS.begin(9600); // initiate GPS serial communication

    while (!Serial);
  Serial.println("Sender Host");
  LoRa.setPins(SS, RST, DIO0); //Sets up the pin configuration for the LoRa module using LoRa.setPins()
  if (!LoRa.begin(433E6)) { //Initializes the LoRa module using LoRa.begin(). The parameter 433E6 sets the frequency to 433 MHz.
    Serial.println("LoRa Error"); //If the LoRa module fails to initialize, the code prints "LoRa Error" and enters an infinite loop.
    delay(100);
    while (1);
  }
  
      // OLED display code start
   delay(250);
   display.begin(Address,true);
  delay(250);
  display.display();
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  gpsLocation();
  //  lora();
  // displayData();

}

void gpsLocation(){
  while(myGPS.available()>0){
    if(gps.encode(myGPS.read())){
      if(gps.location.isValid()){

        latitude = gps.location.lat();
        longitude = gps.location.lng();

        Serial.print("Latitiude: ");
        Serial.print(latitude, 6);
        Serial.print(", Longitude: ");
        Serial.print(longitude, 6);
        Serial.println("");
        // Display Latitude and Longitude over LED
        display.clearDisplay();
        delay(500);
        display.setCursor(0,0);
        display.setTextSize(1);
        display.setCursor(0, 0);
        display.setTextColor(SH110X_WHITE);
        display.print("Lati: ");
        display.print(latitude,6);
        display.println("");
        // Display Longitude
        display.setCursor(0,15);
        display.print("Longi: ");
        display.print(longitude,6);
        display.println("");
        display.display();
        delay(1500);
        display.clearDisplay();
        // LoRa send data
        LoRa.print(latitude);
        // LoRa.print(longitude);
        LoRa.beginPacket();
        LoRa.endPacket();

      }
    }
  }
  // to check GPS is connected properly or not
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }

}


// LoRa send data
/*
void lora(){
  LoRa.beginPacket();
  LoRa.print(latitude);
  LoRa.print(longitude);
  LoRa.endPacket();
  delay(1000);
}

/*
 //Function to display data
 /*void displayData(){
  
  // displayData();
//    clear  buffer
  display.clearDisplay();
   delay(500);
  display.setTextSize(1);
  display.setCursor(0,1);
  display.setTextColor(SH110X_WHITE);
  display.println("Lati: ");
  display.print(latitude);
  display.display();
  delay(2000);
  display.clearDisplay();
}*/
