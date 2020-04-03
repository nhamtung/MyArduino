
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);   // sets the pin as output
}

void loop()
{
  for(int i=100; i<=255; i++)
  {
    analogWrite(9,i);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
    delay(100);
  }
  for(int i=255; i>=100; i--)
  {
    analogWrite(9,i);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
    delay(100);
  }
}
