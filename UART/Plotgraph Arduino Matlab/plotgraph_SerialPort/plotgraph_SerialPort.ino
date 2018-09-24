
#define ADC1 A0  // Analog input pin 
#define ADC2 A1  // Analog input pin 

void setup() 
{
  // initialize serial communications at 115200 bps:
  Serial.begin(115200); 
}

void loop() 
{
  Serial.println(analogRead(ADC1)); 
  delay(100); 
  Serial.println(analogRead(ADC2)); 
  delay(100);                     
}
