
/*
 * Records encoder ticks for each wheel
 * and prints the number of ticks for
 * each encoder every 500ms
 *
 */
 
// pins for the encoder inputs
#define ENCODER_A 2
#define ENCODER_B 4
 
// variables to store the number of encoder pulses
volatile unsigned long Count = 0;
volatile unsigned long Count1 = 0;
volatile unsigned long Count2 = 0;
 
void setup() 
{
  pinMode(ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT);
  
  // initialize hardware interrupts
  attachInterrupt(0, EncoderEvent, CHANGE);
  
  Serial.begin(9600);
}
 
void loop() 
{
  Serial.print("Count: ");
  Serial.println(Count/334);  //vòng
  
  Count1 = Count;
  delay(10000);  //10s
  Count2 = Count;
  Serial.println((Count2-Count1)/334);  //vong/s
  Serial.println();
}
 
// encoder event for the interrupt call
void EncoderEvent() 
{
  if (digitalRead(ENCODER_A) == HIGH) 
  {
    if (digitalRead(ENCODER_B) == LOW) 
      Count++;
    else 
      Count--;
  } 
  else 
  {
    if (digitalRead(ENCODER_B) == LOW) 
      Count--;
    else 
      Count++;
  }
}

