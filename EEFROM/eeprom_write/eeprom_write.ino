/*
 * EEPROM Write
 * 
 * Arduino Uno:        1kb EEPROM storage.  //luu duoc 1024 dia chi
 * Arduino Mega:       4kb EEPROM storage.
 */

#include <EEPROM.h>

int addr = 0;          //address in the EEPROM 
char Str[] = "[192.168.2.115][wifiiot][12051994]";
//int val;           //value

void setup()
{
  for(int i=0 ; i<255 ; i++)
  {
      addr = i; 
      EEPROM.write(addr, 0);   //Write the value to the appropriate byte of the EEPROM. values will remain there when the board is turned off.
      delay(100);
  }
}

void loop() 
{}
