

void setup() {
  Serial.begin(115200);
  Serial.println("Hello world");
}

void loop() {
    while(Serial.available()>0)
    {
      Serial.print(Serial.read());
      Serial.print(" ");
    }
}
