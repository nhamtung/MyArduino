#include <ESP8266WiFi.h>

// Thong so WiFi
const char* ssid = "CH3CHO + H2";  //Thay  ten_wifi bang ten wifi nha ban
const char* password = "ch3ch2oh"; //Thay mat_khau_wifi bang mat khau cua ban

void setup(void)
{
  Serial.begin(115200);  // Khoi dong serial de debug

  WiFi.begin(ssid, password);// Ket noi voi WiFi
  while (WiFi.status() != WL_CONNECTED)  //Kiem tra xem trang thai da ket noi chua neu chua thi in ra dau .
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
// Neu da ket noi duoc voi wifi se in ra dia chi IP
  Serial.println(WiFi.localIP());
}

void loop() 
{
  
}
