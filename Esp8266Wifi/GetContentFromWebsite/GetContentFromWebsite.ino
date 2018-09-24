/*
 * https://hocarm.org/lay-noi-dung-tu-website-voi-esp8266/
 */

#include <ESP8266WiFi.h>

// Thong so Wifi
const char* ssid = "CH3CHO + H2";      //Ten wifi nha ban
const char* password = "ch3ch2oh";   //Mat khau wifi nha ban

// Host
const char* host = "192.168.7.17"; //Trang web de lay du lieu
int value = 0;

void setup() 
{
  Serial.begin(115200); delay(10);
  
// Ket noi voi mang wifi
  Serial.println();Serial.println();
  Serial.print("Ket noi toi mang wifi ");Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi da ket noi");
  Serial.println("Dia chi IP: ");
  Serial.println(WiFi.localIP()); //In ra dia chi IP
}

void loop() 
{
  Serial.print("Ket noi toi web ");
  Serial.println(host);
  
  // Su dung lop WiFiClient de tao ket noi TCP
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort))     //Kiem tra neu khong ket noi dc thi in thong bao
  {
    Serial.println("Khong ket noi duoc");
    return;
  }
  
  // Gui yeu cau toi server
  client.print(String("GET /") + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  delay(5000);
  
  // Doc het cac phan hoi tu server va in ra Serial
  
  Serial.println("Read content from website!");Serial.println();
  while (client.available()) 
  {
    String line = client.readStringUntil('\R');
    Serial.print(line);
  }
  Serial.println();
}
