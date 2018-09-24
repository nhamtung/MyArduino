#include <LiquidCrystal.h>

// Các chân được sử dụng cho việc kết nối LCD Keypad Shield với Arduino Uno
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

// Định nghĩa các giá trị được sử dụng bởi LCD và nút nhấn
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

// Đọc các nút nhấn
int read_LCD_buttons()
{
 adc_key_in = analogRead(0);      // Đọc giá trị các nút nhấn
 // Giá trị các nút nhấn lần lượt nằm gần các giá trị: 0, 144, 329, 504, 741
 // Bằng việc thử sai, mình đã đưa ra được các giá trị bên dưới
 if (adc_key_in > 1000) return btnNONE; // Giá trị lớn hơn 1000 là không có nút nào được nhấn
  if (adc_key_in < 50)   return btnRIGHT;  
 if (adc_key_in < 250)  return btnUP;
 if (adc_key_in < 400)  return btnDOWN;
 if (adc_key_in < 600)  return btnLEFT;
 if (adc_key_in < 650)  return btnSELECT;  



 return btnNONE;  // Nếu không nằm trong khoảng trên thì cũng có nghĩa là không có nút nào được nhấn
}

void setup()
{
 lcd.begin(16, 2);              // Dùng LCD 16, 2
 lcd.setCursor(0,0);            //Thiết lập vị trí con trỏ
 lcd.print("MOI CHON NUT BAM"); // In ra cái mình muốn ghi
}
 
void loop()
{
 lcd.setCursor(9,1);            // Di chuyển con trỏ đến dòng 1, cách ô đầu tiên 9 khoảng
 lcd.print(millis()/1000);      // Đếm s từ khi bắt đầu


 lcd.setCursor(0,1);            // Di chuyển con trỏ đến đầu hàng của hàng 1
 lcd_key = read_LCD_buttons();  // Đọc nút nhấn

 switch (lcd_key)               // Phần lập trình hiển thị nút được nhấn
 {
   case btnRIGHT:
     {
     lcd.print("RIGHT ");
     break;
     }
   case btnLEFT:
     {
     lcd.print("LEFT   ");
     break;
     }
   case btnUP:
     {
     lcd.print("UP    ");
     break;
     }
   case btnDOWN:
     {
     lcd.print("DOWN  ");
     break;
     }
   case btnSELECT:
     {
     lcd.print("SELECT");
     break;
     }
     case btnNONE:
     {
     lcd.print("NONE  ");
     break;
     }
 }

}﻿
