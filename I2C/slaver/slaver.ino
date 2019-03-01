/*
 * i2c Slave Code
 * MEGA2560:
 * PIN 20,21 - SDA,SCL
 * 
 * Arduino Uno:
 * PIN A4,A5 - SDA,SCL
 *
 * Arduino nano:
 * PIN A4,A5 - SDA,SCL
 */

#include <Wire.h>

void setup()
{
  Wire.begin(0x31);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent); // register event
  Serial.begin(115200);           // start serial for output
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop()
{}

void receiveEvent(int howMany)
{
  while(Wire.available()) // chờ cho đến khi có tín hiệu
  {
    char c = Wire.read(); // biến c để lưu dữ liệu nhận được
    
    Serial.println(c);
    
    if(c == 'A') // nếu boad chủ gửi về tín hiệu là A
    {
      digitalWrite(13,HIGH); // chân 13 ở mức High
    }
    if(c == 'B') // nếu tín hiệu boad chủ gửi về là B
    {
      digitalWrite(13,LOW);// chân 13 ở mức Low
    }
  }  
}
