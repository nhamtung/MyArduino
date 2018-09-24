/*
 * D6T-44L-06 PIN:
 *  VCC (5V): Red
 *  GND : Black
 *  SDA : Green
 *  SCL : White
 */

#include <Wire.h>
#include "WireExt.h"

#define D6T_addr 0x0A // Address of OMRON D6T is 0x0A in hex
#define D6T_cmd 0x4C // Standard command is 4C in hex

#define LED_HUMAN 22
 
int rbuf[35]; // Actual raw data is coming in as 35 bytes. Hence the needed for WireExt so that we can handle more than 32 bytes
int tdata[16]; // The data comming from the sensor is 16 elements, in a 16x1 array
float t_PTAT;

int Temp = 0;

void setup()
{
  Wire.begin();
  Serial.begin(115200);

  pinMode(LED_HUMAN, OUTPUT);
  digitalWrite(LED_HUMAN, LOW);

  while(Temp == 0)
  {
      Read_Sensor();
      for(int i=0; i< 16; i++)
        Temp += tdata[i];
      Temp = (int)(Temp/16);
  }
}
 
void loop()
{
   Read_Sensor();      
}

void Read_Sensor()
{
      int i;
      // Begin a regular i2c transmission. Send the device address and then send it a command.
      Wire.beginTransmission(D6T_addr);
      Wire.write(D6T_cmd);
      Wire.endTransmission();
      
      // This is where things are handled differently. Omron D6T output data is 35 bytes and there is a limit here on what Wire can receive. We use WireExt to read the output data 1 piece at a time. We store each byte as an element in rbuf.
      if (WireExt.beginReception(D6T_addr) >= 0) {
        i = 0;
        for (i = 0; i < 35; i++) {
          rbuf[i] = WireExt.get_byte();
        }
        // end the reception routine
        WireExt.endReception();
 
        // Do something with temperature compensation that we don't seem to use currently.
        t_PTAT = (rbuf[0]+(rbuf[1]<<8))*0.1; 
        
        // Calculate the temperature values: add the low temp and the bit shifted high value together. Multiply by 0.1
        for (i = 0; i < 16; i++) {
          tdata[i]=(rbuf[(i*2+2)]+(rbuf[(i*2+3)]<<8))*0.1;
        } 
      }
  
         
      // Use a for loop to output the data. We can copy this from serial monitor and save as a CSV
      for (i=3; i>=0; i--) {
        Serial.print(tdata[i]);Serial.print(",");
      }
      Serial.print("\n");      
      for (i=7; i>=4; i--) {
        Serial.print(tdata[i]);Serial.print(",");
      }
      Serial.print("\n");
      for (i=11; i>=8; i--) {
        Serial.print(tdata[i]);Serial.print(",");
      }
      Serial.print("\n");
      for (i=15; i>=12; i--) {
        Serial.print(tdata[i]);Serial.print(",");
      }
      Serial.println("\n");  
      Serial.print("Temp = ");Serial.println(Temp);
      Serial.print("\n");//*/
      
      int Num = 0; 
      for(int i=0; i<16; i++)
        if((tdata[i] > (Temp+2))&&(tdata[i] < (Temp+7)))
          Num ++;
      Serial.print(Num); 
      if(Num > 3)
      {
        Serial.println("                  Human"); 
        digitalWrite(LED_HUMAN, HIGH);
      }
      else digitalWrite(LED_HUMAN, LOW);
      Serial.print("\n");
      delay(50);
}

