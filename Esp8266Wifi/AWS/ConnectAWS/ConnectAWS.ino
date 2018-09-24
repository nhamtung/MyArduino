/*
   https://hocarm.org/amazon-iot-va-esp8266/
   https://www.youtube.com/watch?v=WJuXv5usXcY
*/

#include <ESP8266WiFi.h>
#include <AmazonIOTClient.h>
#include "ESP8266AWSImplementations.h"

Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;

AmazonIOTClient iotClient;
ActionError actionError;

char *ssid = "CH3CHO + H2";
char *password = "ch3ch2oh";

void setup() {
  Serial.begin(115200);
  delay(10);

  // Connect to WAP
  Serial.print("\nConnecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  iotClient.setAWSRegion("ap-southeast-1");
  iotClient.setAWSEndpoint("amazonaws.com");
  iotClient.setAWSDomain("avt6g3kvwjn2o.iot.ap-southeast-1.amazonaws.com");
  iotClient.setAWSPath("/things/Tutorial/shadow");
  iotClient.setAWSKeyID("AKIAJ3RDBZS7WIJ5PHWQ");     //anh LongLH cung cap
  iotClient.setAWSSecretKey("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");  //anh LongLH cung cap
  iotClient.setHttpClient(&httpClient);
  iotClient.setDateTimeProvider(&dateTimeProvider);
}

void loop()
{
  UpdateToShadow();
  delay(10000);
}
void UpdateToShadow()
{
  char shadow[100];
  //strcpy(shadow, "{\"state\":{\"reported\": {\"foobar\": \"bar\"}}}");
  strcpy(shadow, "{\"state\":{\"reported\":{\"test_value1\":123, \"test_value2\":234}}}");

  Serial.print("\nTrying to send data: ");
  Serial.println(shadow);
  
  char* result = iotClient.update_shadow(shadow, actionError);
  Serial.print("\tRESULT: ");
  Serial.println(result);
  Serial.print("\tactionError: ");
  Serial.println(actionError);
}

