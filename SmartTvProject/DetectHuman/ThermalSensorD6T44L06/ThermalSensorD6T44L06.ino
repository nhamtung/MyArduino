/*
 * Arduino nano
 * I2C protocol
 *  
 *  D6T-44L-06 PIN:
 *  VCC (5V): Red
 *  GND : Black
 *  SDA : Green
 *  SCL : White
 */

#include <Wire.h>
#include "WireExt.h"

#define D6T_addr 0x0A // Address of OMRON D6T is 0x0A in hex
#define D6T_cmd 0x4C // Standard command is 4C in hex
#define COUNT 35
#define DATA 16

#define LED_MODE 13 
int rbuf[35]; // Actual raw data is coming in as 35 bytes. Hence the needed for WireExt so that we can handle more than 32 bytes
int tdata[16]; // The data comming from the sensor is 16 elements, in a 16x1 array
float t_PTAT;
int temp = 0;

bool flagHuman = false;
String stateHuman = "NOOO MAN";

void setup(){
    Wire.begin(D6T_addr);  
    Serial.begin(115200);
    
    while(temp == 0){
        ReadSensorD6T44L06();
        for(int i=0; i<DATA; i++)
            temp += tdata[i];
        temp = (int)(temp/16);
        if(temp <25) temp = 25;
        if(temp > 27) temp = 27;
        Serial.print("Temp = "); Serial.println(temp);
    }
    
    delay(3000);
    Serial.println("\tREADY!");
}

void loop(){
    DetectHuman();
    delay(200);
}

void DetectHuman(){
    if(ReadSensorD6T44L06() > 3){
        flagHuman = true;
        stateHuman = "MAN";
    }else if(ReadSensorD6T44L06() < 2){
        flagHuman = false;
        stateHuman = "NO MAN";            
    }
}

 // Đọc giá trị cảm biến thân nhiệt
int ReadSensorD6T44L06() {
      // Begin a regular i2c transmission. Send the device address and then send it a command.
      Wire.beginTransmission(D6T_addr);
      Wire.write(D6T_cmd);
      Wire.endTransmission();
      
      // This is where things are handled differently. Omron D6T output data is 35 bytes and there is a limit here on what Wire can receive. We use WireExt to read the output data 1 piece at a time. We store each byte as an element in rbuf.
      if (WireExt.beginReception(D6T_addr) >= 0) {
          for (byte i = 0; i < COUNT; i++) {
              rbuf[i] = WireExt.get_byte();
          }
          WireExt.endReception();  // end the reception routine
          t_PTAT = (rbuf[0]+(rbuf[1]<<8))*0.1; // Do something with temperature compensation that we don't seem to use currently.
          
          // Calculate the temperature values: add the low temp and the bit shifted high value together. Multiply by 0.1
          for (byte i = 0; i < DATA; i++) {
              tdata[i]=(rbuf[(i*2+2)]+(rbuf[(i*2+3)]<<8))*0.1;
          } 
      }
      DisplayTemperature();
      
      byte countFlagHuman = 0; 
      for(byte i=0; i<DATA; i++)
        if((tdata[i] > (temp+3))&&(tdata[i] < (temp+8)))
            countFlagHuman ++;
      Serial.print("Count Flag Human: ");Serial.println(countFlagHuman); 
      
      return countFlagHuman;
      delay(10);
}

// Hiển thị mảng dữ liệu của cảm biến thân nhiệt
void DisplayTemperature(){
      int i;
      for (i=3; i>=0; i--) {
        Serial.print(tdata[i]);Serial.print(",");
      }
      Serial.println();      
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
      Serial.print("Temp = ");Serial.println(temp);
      Serial.print("t_PTAT = ");Serial.println(t_PTAT);
      Serial.print("\n");
}
