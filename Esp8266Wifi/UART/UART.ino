
#include <ESP8266WiFi.h>

// Thong so Wifi
const char* ssid = "CH3CHO + H2";      //Ten wifi nha ban
const char* password = "ch3ch2oh";   //Mat khau wifi nha ban
// Host
const char* host = "192.168.7.17";
const int port = 80;

WiFiClient client;

void connect_to_wifi()
{
  WiFi.begin(ssid, password);
  int tries=0;
  for(tries=0;tries<20 && WiFi.status()!=WL_CONNECTED;++tries)
  {
    digitalWrite(D0,(tries&1)==1?HIGH:LOW);
    Serial.print(".");
    delay(500);
  }
  if (tries>=20)
  {
    Serial.println("Failed to connect to WiFi");
  }
  else
  {
    Serial.println("Connected to WiFi");
    if (client.connect(host, port))
    {
      Serial.println("Connected to server");
      client.println("Connected");
    }
    else
    {
      Serial.println("Failed to connect to server");
    }
  }
}

void setup() {
    Serial.begin(115200);
    //while (!Serial) delay(10);
    
    connect_to_wifi();
    pinMode(D0,OUTPUT);
    digitalWrite(D0,LOW);
}

void loop() {
    digitalWrite(D0,HIGH);
    delay(100);
    digitalWrite(D0,LOW);
    delay(100);

    Serial.println("Hello!");
    int av=Serial.available();
    if (av>0)
    {
      client.println(av);
      for(int i=0;i<av;++i)
      {
        int c=Serial.read();
        client.print(char(c));
      }
    }
}
