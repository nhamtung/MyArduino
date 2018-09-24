#include "LedBlink.h"

Morse Morse(13);

void setup()
{
}

void loop()
{
  Morse.dot(); 
  Morse.dot(); 
  Morse.dot();
  
  Morse.dash(); 
  Morse.dash(); 
  Morse.dash();
  
  Morse.dot(); 
  Morse.dot(); 
  Morse.dot();
  
  delay(3000);
}
