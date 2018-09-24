/*
 * EEPROM Write
 * 
 * Arduino Uno:        1kb EEPROM storage.
 * Arduino Mega:       4kb EEPROM storage.
 */

#include <EEPROM.h>

//int a = 0;
//int value;
char Str[255];

void setup()
{
  Serial.begin(115200);
}

void loop()
{
/*  value = EEPROM.read(a);

  Serial.print(a);
  Serial.print("\t");
  Serial.print(value);
  Serial.println();

  a = a + 1;
  if (a == 260)
    a = 0;//*/

    for(int i=0; i<35; i++)
    {
        Str[i] = EEPROM.read(i);
        Serial.print(Str[i]);
    }
    Serial.println();
    delay(5000);
}
