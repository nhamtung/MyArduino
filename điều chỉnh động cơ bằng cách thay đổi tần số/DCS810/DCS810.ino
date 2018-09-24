void setup() 
{
  pinMode(13, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}

// the loop function runs over and over again forever
void loop() 
{
  //digitalWrite(9, HIGH);
  delay(5); 
 // digitalWrite(13, HIGH);  
  digitalWrite(10, LOW);  
  delay(0.25); 
 // digitalWrite(13, LOW);  
  digitalWrite(10, HIGH);
  delay(0.25);             
}
