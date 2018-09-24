// out - PIN D4

void setup() {
  Serial.begin(115200);
}

void loop() {
  //int state = digitalRead(4);  // PIN D4
  float state = analogRead(A2);  // PIN A2
  
  Serial.println((state/330) *1000); 
  delay(10);
}
