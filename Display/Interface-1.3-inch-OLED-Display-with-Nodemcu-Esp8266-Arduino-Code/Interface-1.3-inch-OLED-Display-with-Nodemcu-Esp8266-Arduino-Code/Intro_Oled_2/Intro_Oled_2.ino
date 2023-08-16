#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// Define address of OLED display
#define Address 0x3C
// define height and width
#define width 128
#define height 64
// there is no reset pin in display so we send -1 to the nodemcu
#define reset -1
// pass all the aboce parameters(height, width, wire, reset)
Adafruit_SH1106G display = Adafruit_SH1106G(width, height, &Wire, reset);

void setup() {
  Serial.begin(9600);
    // wait for display to power up
  delay(250);
  // start the display inside circuitry current
  display.begin(Address,true);
  // display.setContrast(1);
  display.display();
  delay(2000);
}

void loop() {
//  displayMessage();
}
void displayMessage(){
  // clear buffer
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0,20);
  display.setTextColor(SH110X_WHITE);
  display.print("I'm OLED Display");
  display.println("");
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("OLED Display");
  display.display();
  delay(2000);
  // display.println("");
//  display.clearDisplay();
//  display.println("Hi, how are you");
}
