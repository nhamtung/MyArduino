/*
 * Arduino Uno
 * interrup 0 - PIN 2 - Phase A
 * Phase B - PIN 3
 * Baudrate = 115200
 */

const int interrupt0 = 0;
const int phase_a = 2;
//const int phase_b = 3;

long pulse = 0;

void setup() 
{
  attachInterrupt (interrupt0, int_, FALLING);
  pinMode(phase_a, INPUT_PULLUP);
//  pinMode(phase_b, INPUT_PULLUP);

  Serial.begin(115200);
}

void loop() 
{
  Serial.println(pulse);
  delay(10);
}

void int_()
{
//  if(digitalRead (phase_b) == LOW)
  {
    pulse++;
  }
 /* else
  {
    pulse--;
  }//*/
}

