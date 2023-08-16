/*
 * Subscribe Tech Vegan for More Hardware & Software Tech Videos
 * Program by: Ashish Vegan https://www.ashishvegan.com
 * For Help - Contact WhatsApp +919890345539
 * technologyvegan@gmail.com
 * Get Harware & Software Academic Projects
 * Code Courtesy: Lora.h
Youtube video link: https://www.youtube.com/watch?v=wH483V8fnN8
Channel Name: "Subscribe Tech Vegan"
 */
#include <LoRa.h>
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
//pass above parameters
Adafruit_SH1106G display = Adafruit_SH1106G(width, height, &Wire, reset);


String data = "I'm Receiver";


void setup()
{
  Serial.begin(9600);
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

// defining pin for LoRa
/*
16 -> D0
0 ->  D3
2 ->  D4
3 ->  RX
14 -> D5
12 -> D6
13 -> D7
15 -> D8

*/
  // SPI.begin(14, 12, 13, 15);  // SCK, MISO, MOSI, NSS (ESP8266 pins)
  // LoRa.setPins(16,2,3);  // SS, RST, DI0 (ESP8266 pins)


  
  // displayData();
}
void loop()
{
  Serial.print("Sending Data: ");
  Serial.println(data);
  LoRa.beginPacket(); //Begins a new LoRa packet using LoRa.beginPacket()
  LoRa.print(data); //Sends the data string over LoRa using LoRa.print()
  LoRa.endPacket(); //Ends the LoRa packet using LoRa.endPacket()
  delay(3000);
   displayData();
}


 void displayData(){
  
//   // clear  buffer
  display.clearDisplay();
   delay(500);
  display.setTextSize(1);
  display.setCursor(0,1);
  display.setTextColor(SH110X_WHITE);
  display.println("Sender: ");
  display.print(data);
  display.display();
  delay(2000);
  display.clearDisplay();
}
/*
Summary
Overall, this code sets up the LoRa module, initializes the serial communication,
 and sends the "Subscribe Tech Vegan" string repeatedly over LoRa at a 433 MHz
  frequency with a 3-second delay between transmissions.
*/

