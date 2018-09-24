#define LED_PIN 9
 
void setup() 
{
  pinMode(LED_PIN, OUTPUT);
}
 
void loop() 
{
  // Make LED brighter time-to-time
  for (int i = 0; i < 256; i++)
  {
    analogWrite(LED_PIN, i);
    delay(10);
  }
 
  // Stop for a while
  delay(1000);
 
  // Make LED dimmer time-to-time
  for (int i = 255; i >= 0; i--)
  {
    analogWrite(LED_PIN, i);
    delay(10);
  }
 
  // Stop for a while
  delay(1000);
}
