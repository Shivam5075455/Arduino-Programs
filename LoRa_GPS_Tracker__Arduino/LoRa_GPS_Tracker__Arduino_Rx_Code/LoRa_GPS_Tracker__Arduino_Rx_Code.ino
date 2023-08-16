/*
  //Receiver
  
 
*/
#include <SPI.h>              // include libraries
#include <LoRa.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 int Buzzer=5;
 int button=4;
 int buttonState;
 int Distance;
 boolean Bflag = false;
 
String SenderNode = "";
String outgoing;              // outgoing message

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xFF;     // address of this device
byte destination = 0xBB;      // destination to send to
long lastSendTime = 0;        // last send time
int interval = 2000;          // interval between sends
 
String incoming = "";
 String statusmessage = "";

int Sensor1 = 0; // Latitude
int Sensor2 = 0; // Longitude
int Sensor3 = 0; // Status
 
String DayNight = "";
 
void setup() {
  Serial.begin(9600);                   // initialize serial
  pinMode(Buzzer,OUTPUT);
   pinMode(button,INPUT_PULLUP);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  delay(500);
  display.clearDisplay();
  display.setTextColor(WHITE);
 
  if (!LoRa.begin(433E6)) {             // initialize ratio at 915 MHz
    Serial.println("LoRa init failed. Check your connections.");
    while (true);                       // if failed, do nothing
  }
 
 // Serial.println("LoRa init succeeded.");
}
 
void loop() {
 
  // parse for a packet, and call onReceive with the result:
  if (millis() - lastSendTime > interval) {

    if ( (digitalRead(button) == LOW) && ( Bflag == false ) )
    {
      buttonState = 1;
      Bflag = true;
    }

       if ( (digitalRead(button) == HIGH )&& (Bflag == true))
    {
      buttonState = 0;
      Bflag = false;
    }
  
statusmessage = statusmessage + buttonState + "," ;
        sendMessage(statusmessage);
        delay(50);
        statusmessage = "";

     lastSendTime = millis();  
  }
   
  onReceive(LoRa.parsePacket());
    
  }
 
 
void onReceive(int packetSize) {
  if (packetSize == 0) return;          // if there's no packet, return
 
  // read packet header bytes:
  int recipient = LoRa.read();          // recipient address
  byte sender = LoRa.read();            // sender address
  if( sender == 0XBB )
  SenderNode = "Node1:";
  byte incomingMsgId = LoRa.read();     // incoming msg ID
  byte incomingLength = LoRa.read();    // incoming msg length
 
 
  while (LoRa.available()) {
    incoming += (char)LoRa.read();
  }
 
  if (incomingLength != incoming.length()) {   // check length for error
    //Serial.println("error: message length does not match length");
    ;
    return;                             // skip rest of function
  }
 
//  // if the recipient isn't this device or broadcast,
//  if (recipient != Node1 && recipient != MasterNode) {
//   // Serial.println("This message is not for me.");
//    ;
//    return;                             // skip rest of function
//  }
 
  // if message is for this device, or broadcast, print details:
  //Serial.println("Received from: 0x" + String(sender, HEX));
  //Serial.println("Sent to: 0x" + String(recipient, HEX));
  //Serial.println("Message ID: " + String(incomingMsgId));
 // Serial.println("Message length: " + String(incomingLength));
 // Serial.println("Message: " + incoming);
  //Serial.println("RSSI: " + String(LoRa.packetRssi()));
 // Serial.println("Snr: " + String(LoRa.packetSnr()));
 // Serial.println();
 
//Serial.println("received value");
 
String q = getValue(incoming, ',', 0); // Latitude
String r = getValue(incoming, ',', 1); // Longitude
String s = getValue(incoming, ',', 2); // Status
String t = getValue(incoming, ',', 3); // Status

Sensor1 = q.toDouble();  // latitude
Sensor2 = r.toDouble(); // longitude
Sensor3 = s.toInt(); // status
Distance = t.toInt();
//Serial.println(q);
//Serial.println(r);
//Serial.println(s);
 
if (Sensor3==1)
{
  digitalWrite(Buzzer,HIGH);
  }
  else 
{
  digitalWrite(Buzzer,LOW);
  }
incoming = "";

 
    //clear display
  display.clearDisplay();
 

 
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.print(q);        // Latitude
   
    display.setTextSize(2);
  display.setCursor(0, 30);
  display.print(r);       // Longitude
 
  display.setTextSize(2);
  display.setCursor(0, 50);
  display.print("S:" + s +" D:"+Distance); // Status and distance


 
display.display(); 
}
 
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void sendMessage(String outgoing) {
  LoRa.beginPacket();                   // start packet
  LoRa.write(destination);              // add destination address
  LoRa.write(localAddress);             // add sender address
  LoRa.write(msgCount);                 // add message ID
  LoRa.write(outgoing.length());        // add payload length
  LoRa.print(outgoing);                 // add payload
  LoRa.endPacket();                     // finish packet and send it
  msgCount++;                           // increment message ID
}
