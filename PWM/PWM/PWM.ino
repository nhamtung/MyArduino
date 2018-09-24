
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);   // sets the pin as output
  pinMode(8, OUTPUT);
}

void loop()
{
  digitalWrite(8, HIGH);
  analogWrite(9,128);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
}
