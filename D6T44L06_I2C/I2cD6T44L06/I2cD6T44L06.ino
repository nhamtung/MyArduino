/*
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
int rbuf[35];

void setup()
{
  Wire.begin(D6T_addr);               // join i2c bus with address #4
  Wire.onReceive(receiveEvent);   // register event
  Serial.begin(115200);           // start serial for output
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop() {
    Wire.beginTransmission(D6T_addr);
    Wire.write(D6T_cmd);
    Wire.endTransmission();

    if (WireExt.beginReception(D6T_addr) >= 0) {
        for (byte i = 0; i < 35; i++) {
            rbuf[i] = WireExt.get_byte();
            Serial.print(rbuf[i]);
        }
        WireExt.endReception();  // end the reception routine
    }
    
    Serial.println();
    delay(500);
}

void receiveEvent(int howMany)
{
  Serial.println("Interrupt");
  while(Wire.available()) // chờ cho đến khi có tín hiệu
  {
    char c = Wire.read(); // biến c để lưu dữ liệu nhận được
    Serial.print(c);
  }  
}
