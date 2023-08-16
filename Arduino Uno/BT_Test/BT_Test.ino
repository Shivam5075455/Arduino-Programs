#include <SoftwareSerial.h>

const int BT_TX_PIN = 0; // HC-05 TX pin connected to Arduino Uno digital pin 2
const int BT_RX_PIN = 1; // HC-05 RX pin connected to Arduino Uno digital pin 3

SoftwareSerial btSerial(BT_TX_PIN, BT_RX_PIN);

void setup() {
  Serial.begin(9600); // Start serial communication with the PC for debugging
  btSerial.begin(9600); // Start serial communication with the HC-05 Bluetooth module
}

void loop() {
  char sender[100];
  scanf("%c",&sender[100]);
  sendDataOverBluetooth(sender); // Send the data
  delay(2000);
  //delay(2000); // Wait for 5 seconds (adjust this interval as needed)
}

void sendDataOverBluetooth(const char* data) {
  btSerial.println(data);
  Serial.println(data);
}






/*


#define LED1 13
int data =0;

void setup() {
  pinMode(LED1,OUTPUT);
  digitalWrite(LED1,0);
  Serial.begin(9600); // Start serial communication with the PC for debugging
}

void loop() {
  if(Serial.available() > 0){
    data = Serial.read();

      if(data == '0'){
        digitalWrite(LED1, 0);
        Serial.println("LED OFF");
      }
      else if(data == '1'){
        digitalWrite(LED1, 1);
        Serial.println("LED ON");
      }
  }
}
*/
