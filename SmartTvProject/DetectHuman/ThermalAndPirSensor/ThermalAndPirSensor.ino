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
#define LED_MODE 13 

const int dataPin = 4;     // PIN D4
const int ledPin =  13;      // the number of the LED pin

int rbuf[35]; // Actual raw data is coming in as 35 bytes. Hence the needed for WireExt so that we can handle more than 32 bytes
int tdata[16]; // The data comming from the sensor is 16 elements, in a 16x1 array
float t_PTAT;
int t_PEC;
int temp = 0;

String stateHuman = "NOOO MAN";
byte countFlagHuman;

void setup(){
    Wire.begin(D6T_addr);  
    Serial.begin(115200);
    
    pinMode(dataPin, INPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    Serial.println("Setup!"); 
}

void loop(){
    if (digitalRead(dataPin) == HIGH) {
        digitalWrite(ledPin, HIGH);
        Serial.println("MOVING!");
        DetectHuman();
    } else {
        digitalWrite(ledPin, LOW);
        Serial.println("STOP!");
    }
    delay(100);
}

void DetectHuman(){
    countFlagHuman = 0; 
    if(ReadSensorD6T44L06()){
        if(countFlagHuman > 2)
            stateHuman = "MAN";
        else if(countFlagHuman < 2)
            stateHuman = "NO MAN";
        Serial.println("\t\t\t" + stateHuman);
    } else {
        Serial.println("\t\t\t ERROR");          
    }
}

 // Đọc giá trị cảm biến thân nhiệt
bool ReadSensorD6T44L06() {
      // Begin a regular i2c transmission. Send the device address and then send it a command.
      Wire.beginTransmission(D6T_addr);
      Wire.write(D6T_cmd);
      Wire.endTransmission();
      
      // This is where things are handled differently. Omron D6T output data is 35 bytes and there is a limit here on what Wire can receive. We use WireExt to read the output data 1 piece at a time. We store each byte as an element in rbuf.
      if (WireExt.beginReception(D6T_addr) >= 0) {
          for (byte i = 0; i < 35; i++) {
              rbuf[i] = WireExt.get_byte();
          }
          WireExt.endReception();  // end the reception routine
          t_PTAT = (rbuf[0]+(rbuf[1]<<8))*0.1; // Do something with temperature compensation that we don't seem to use currently.
          
          // Calculate the temperature values: add the low temp and the bit shifted high value together. Multiply by 0.1
          for (byte i = 0; i < 16; i++) {
              tdata[i]=(rbuf[(i*2+2)]+(rbuf[(i*2+3)]<<8))*0.1;
          } 
          t_PEC = rbuf[34];
      }
        
      if(!D6T_checkPEC(rbuf, 34))
          return false;
          
      for(byte i=0; i<16; i++){
          if((tdata[i] > t_PTAT)&&(tdata[i] < t_PTAT+5))
              countFlagHuman ++;
      }
      
      DisplayTemperature();
      return true;
}

//bool D6T_checkPEC(int buf[], int pPEC)
//{
//    unsigned char crc;
//    crc = calc_crc( 0x14 );
//    crc = calc_crc( 0x4C ^ crc );
//    crc = calc_crc( 0x15 ^ crc );
//    for(int i=0;i<pPEC;i++){
//        crc = calc_crc( buf[i] ^ crc );
//    }
//
//    Serial.print("crc = ");Serial.println(crc);
//    Serial.print("t_PEC = ");Serial.println(t_PEC);
//    if (crc == buf[pPEC])
//        return true;
//    else return false;
//}
bool D6T_checkPEC(int buf[] , int pPEC )
{
    unsigned char crc;
    int i;
    crc = calc_crc( 0x15 );
    for(i=0;i<pPEC;i++){
        crc = calc_crc( buf[i] ^ crc );
    }

    if (crc == buf[pPEC])
        return true;
    else return false;
}

unsigned char calc_crc(unsigned char data)
{
    int index;
    unsigned char temp;

    for(index = 0; index < 8; index++){
        temp = data;
        data <<= 1;
        if(temp & 0x80) data ^= 0x07;
    }
    return data;
}

// Hiển thị mảng dữ liệu của cảm biến thân nhiệt
void DisplayTemperature(){
      int i;
      for (i=3; i>=0; i--) {
        Serial.print(tdata[i]);Serial.print(","); }
      Serial.println();      
      for (i=7; i>=4; i--) {
        Serial.print(tdata[i]);Serial.print(","); }
      Serial.print("\n");
      for (i=11; i>=8; i--) {
        Serial.print(tdata[i]);Serial.print(","); }
      Serial.print("\n");
      for (i=15; i>=12; i--) {
        Serial.print(tdata[i]);Serial.print(","); }
      Serial.println("\n"); 
       
      Serial.print("t_PTAT = ");Serial.println(t_PTAT);
      Serial.print("Count Flag Human: ");Serial.println(countFlagHuman); 
      Serial.print("\n");
}
