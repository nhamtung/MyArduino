char data_send[] = "TungNV send \n";

void setup() {
  // initialize serial:
  Serial.begin(115200);
  Serial.println("READY!");
}

void loop() 
{
  int bytesSent = Serial.write(data_send); //send the string and return the length of the string.
  delay(1000);  
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    Serial.println(inChar);
  }
}
