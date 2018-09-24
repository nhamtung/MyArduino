
#include <EEPROM.h>

void setup() 
{
   pinMode(13, OUTPUT);

   for (int i = 0 ; i < 100; i++) 
   {
     EEPROM.write(i, 0);
   }

   digitalWrite(13, HIGH);
}

void loop() 
{}
