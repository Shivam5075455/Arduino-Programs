#define LED1 13

void setup() {
  Serial.begin(115200);
  pinMode(LED1, OUTPUT);
}

void loop() {
  digitalWrite(LED1, 1);
  delay(3000);
  digitalWrite(LED1, 0);
  delay(3000);
  Serial.print("ON");
  Serial.print(LED1);
  
  }
