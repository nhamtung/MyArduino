//Chương trình HIỂN THỊ NHIỆT ĐỘ TRÊN LCD
//Chương trình được viết bởi Huỳnh Minh Phú, email: hmphubt@gmail.com
//facebook của người viết chương trình: https://www.facebook.com/profile.php?id=100008315270063
//Các bạn có thể tham khảo thêm phần cảm biến LM35 tại đây: Lập trình vi điều khiển-Phần 32-Đo nhiệt độ bằng cảm biến nhiệt LM35 với Arduino
//BẮT ĐẦU
//Các khai báo cho màn hình LCD
#include <LiquidCrystal.h>
// Các chân được sử dụng cho việc kết nối LCD Keypad Shield với Arduino Uno
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
//Khai báo biến cho cảm biến nhiệt LM35
float nhietdo;
int chanlaynhiet=1;//Chọn chân A1 làm chân lấy tín hiệu nhiệt độ.

void setup()
{
 lcd.begin(16, 2);              // Dùng LCD 16, 2
 }
 
void loop()
{
  nhietdo=analogRead(chanlaynhiet);//Lấy nhiệt độ từ LM35
  nhietdo=(nhietdo*5.0*1000.0/1024.0)/10;//Chuyển nhiệt độ lấy được sang độ C
  lcd.setCursor(2,0);            //Thiết lập vị trí con trỏ
  lcd.print("NHIET DO LA:"); // In ra cái mình muốn ghi
  lcd.setCursor(0,1);
  lcd.print(nhietdo);
  lcd.print(" do C");
  delay(1000);//Sau 1s thì cập nhật thông số nhiệt độ
  }﻿
