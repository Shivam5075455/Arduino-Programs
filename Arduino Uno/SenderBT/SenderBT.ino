#include <SoftwareSerial.h>

const int BT_TX_PIN = 0; // HC-05 TX pin connected to Arduino Uno digital pin 2
const int BT_RX_PIN = 1; // HC-05 RX pin connected to Arduino Uno digital pin 3

SoftwareSerial btSerial(BT_TX_PIN, BT_RX_PIN);

void setup() {
  Serial.begin(9600); // Start serial communication with the PC for debugging
  btSerial.begin(9600); // Start serial communication with the HC-05 Bluetooth module
}

void loop() {
  if (Serial.available()) {
    char data = Serial.read();
    btSerial.print(data); // Send the data to the receiver over Bluetooth
  }

  if (btSerial.available()) {
    char data = btSerial.read();
    Serial.print(data); // Print the received data to the Serial Monitor
  }
}
