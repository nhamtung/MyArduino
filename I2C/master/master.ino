/*
 * i2c Master Code
 * MEGA2560:
 * PIN 20,21 - SDA,SCL
 * 
 * Arduino nano:
 * PIN A4,A5 - SDA,SCL
 */


#include <Wire.h>

void setup()
{
  Wire.begin(); // Khởi tạo thư viện i2c
  Serial.begin(115200);

  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}
 
void loop()
{
    Wire.beginTransmission(0xA0); // Bắt đầu truyền dữ liệu về địa chỉ 0xA0
    Wire.write('A'); // Truyền ký tự A (i2c)
    Serial.println("A");
    Wire.endTransmission(); // kết thúc truyền dữ liệu
    delay(1000);
    
//    Wire.beginTransmission(0xA0); // Bắt đầu truyền dữ liệu về địa chỉ 0xA0
//    Wire.write('B'); // Truyền ký tự B (i2c)
//    Serial.println("B");
//    Wire.endTransmission(); // kết thúc truyền dữ liệu
//    delay(1000);
}
