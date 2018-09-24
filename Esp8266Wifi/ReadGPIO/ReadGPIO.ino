
#include <ESP8266WiFi.h>

void setup(void)
{
  Serial.begin(115200);
  pinMode(5, INPUT);// Khoi tao GPIO 5 la input
}
void loop() 
{
  Serial.print("Trang thai cua GPIO 5: ");
  Serial.println(digitalRead(5));

  delay(1000);
}
