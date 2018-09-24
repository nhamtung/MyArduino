/*
 * Arduino mega 2560 hoặc UNO
 */

#include <LiquidCrystal.h>
 
//Khởi tạo với các chân
LiquidCrystal lcd(8, 9, 10, 4, 5, 6, 7);
/////////////////(RS,EN,RW,D4,D5,D6,D7) 

void setup() 
{
  lcd.begin(16, 2);
  lcd.print("TTCS WELCOMS YOU");
  delay(1000);
}
 
void loop() 
{
  lcd.setCursor(0,1);    // đặt con trỏ vào cột 0, dòng 1
  lcd.print("I'M COMING");
}
