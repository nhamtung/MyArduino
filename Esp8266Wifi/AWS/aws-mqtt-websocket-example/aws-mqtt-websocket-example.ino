/*
 * https://www.youtube.com/watch?v=doqLJIQagJY
 */

#include <Arduino.h>
#include <Stream.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

//AWS
#include "sha256.h"
#include "Utils.h"

//WEBSockets
#include <Hash.h>
#include <WebSocketClient.h>

//MQTT PAHO
#include <SPI.h>
#include <IPStack.h>
#include <Countdown.h>
#include <MQTTClient.h>

//AWS MQTT Websocket
#include "Client.h"
#include "AWSWebSocketClient.h"
#include "CircularByteBuffer.h"

//AWS IOT config, change these:
char wifi_ssid[]       = "CH3CHO + H2";
char wifi_password[]   = "ch3ch2oh";
char aws_key[]         = "AKIAJ3RDBZS7WIJ5PHWQ";
char aws_secret[]      = "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";
int port = 443;

char aws_region[]      = "ap-southeast-1";
char aws_endpoint[]    = "avt6g3kvwjn2o.iot.ap-southeast-1.amazonaws.com";
const char* aws_topic  = "$aws/things/Tutorial/shadow/update";

//MQTT config
const int maxMQTTpackageSize = 512;
const int maxMQTTMessageHandlers = 1;

//VM5GA Device
byte num2=0, num3=0, num4=0, num6=0, num20=0;
byte dataReceive[20];

ESP8266WiFiMulti WiFiMulti;

AWSWebSocketClient awsWSclient(1000);

IPStack ipstack(awsWSclient);
MQTT::Client<IPStack, Countdown, maxMQTTpackageSize, maxMQTTMessageHandlers> *client = NULL;


//# of connections
long connection = 0;    
String reader = "", tag = "";
String title = "";
bool flagTitle = false;
bool flagContent = false;
bool flagEnd = false;

//generate random mqtt clientID
char* generateClientID () {
    char* cID = new char[23]();
    for (int i=0; i<22; i+=1)
        cID[i]=(char)random(1, 256);
    return cID;
}

//count messages arrived
int arrivedcount = 0;

//callback to handle mqtt messages
void messageArrived(MQTT::MessageData& md)
{
    MQTT::Message &message = md.message;
  
    Serial.print("Message ");Serial.print(++arrivedcount);
    Serial.print(" arrived: qos "); Serial.print(message.qos);
    Serial.print(", retained ");Serial.print(message.retained);
    Serial.print(", dup ");Serial.print(message.dup);
    Serial.print(", packetid ");Serial.println(message.id);
    Serial.print("Payload: ");
    char* msg = new char[message.payloadlen+1]();
    memcpy (msg,message.payload,message.payloadlen);
    Serial.println(msg);
    delete msg;
}

void ConnectWifi(){
    //fill with ssid and wifi password
    WiFiMulti.addAP(wifi_ssid, wifi_password);
    Serial.print("\nConnecting to wifi ");  
    Serial.print(wifi_ssid);
    while(WiFiMulti.run() != WL_CONNECTED) {
        delay(100);
        Serial.print (".");
    }  
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");Serial.println(WiFi.localIP());
}

void SetParameterAWS(){
    //fill AWS parameters    
    Serial.println ("\nFill AWS parameters!");
    awsWSclient.setAWSRegion(aws_region);
    awsWSclient.setAWSDomain(aws_endpoint);
    awsWSclient.setAWSKeyID(aws_key);
    awsWSclient.setAWSSecretKey(aws_secret);
    awsWSclient.setUseSSL(true);
}

//connects to websocket layer and mqtt layer
bool connect () {
    if (client == NULL) {
        client = new MQTT::Client<IPStack, Countdown, maxMQTTpackageSize, maxMQTTMessageHandlers>(ipstack);
    } else {
      if (client->isConnected ()) {    
            client->disconnect ();
        }  
        delete client;
        client = new MQTT::Client<IPStack, Countdown, maxMQTTpackageSize, maxMQTTMessageHandlers>(ipstack);
    }

    delay (100);
    Serial.print ("millis: ");Serial.print (millis ());
    Serial.print (" - connect: ");Serial.print (++connection);
    Serial.print (" - (");Serial.print (ESP.getFreeHeap ());Serial.println (")");

    int rc = ipstack.connect(aws_endpoint, port);
    if (rc != 1){
        Serial.println("error connection to the websocket server");
        return false;
    } else {
        Serial.println("websocket layer connected");
    }

    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    char* clientID = generateClientID ();
    data.clientID.cstring = clientID;
    rc = client->connect(data);
    delete[] clientID;
    if (rc != 0){
        Serial.print("error connection to MQTT server");
        Serial.println(rc);
        return false;
    }
    Serial.println("MQTT connected!");
    return true;
}

//subscribe to a mqtt topic
void subscribe () {
   //subscript to a topic
    int rc = client->subscribe(aws_topic, MQTT::QOS0, messageArrived);
    if (rc != 0) {
        Serial.print("rc from MQTT subscribe is ");
        Serial.println(rc);
        return;
    }
    Serial.println("MQTT subscribed!");
}

//send a message to a mqtt topic
void sendmessage (int tag, int num) {
    //send a message
    Serial.print("tag ");Serial.print(tag);
    Serial.print(", num ");Serial.println(num);
    MQTT::Message message;
    char buf[100];
    //strcpy(buf, "{\"state\":{\"reported\":{\"on\": false}, \"desired\":{\"on\": false}}}");
    //strcpy(buf, "{\"state\":{\"reported\":{\"EPC\": \"BB\"}, \"desired\":{\"Tag\": 4}}}");
    //strcpy(buf, "{\"state\":{\"desired\":{\"StartBit\": \"BB\"}, \"reported\":{\"EPC\": \"04\"}, \"delta\":{\"StopBit\": \"7E\"}}}");
    //strcpy(buf, "{\"state\":{\"desired\":{\"StartBit\": \"BB\"}, \"reported\":{\"EPC\": \"04\"}}}");
    //sprintf(buf, "{\"state\":{\"reported\":{\"led\":%d}}}", true);
    //sprintf(buf, "{\"state\":{\"reported\":{\"LED\":%d}}}", 12);
    sprintf(buf, "{\"state\":{\"reported\":{\"Tag %d\":%d}}}",tag , num);
    
    message.qos = MQTT::QOS0;
    message.retained = false;
    message.dup = false;
    message.payload = (void*)buf;
    message.payloadlen = strlen(buf)+1;
    int rc = client->publish(aws_topic, message); 
    
    Serial.println("Send tag success!");
}

void ReadSerial()
{
    ///Receive Data
    int n=0;   
    for(int i=0; i<sizeof(dataReceive); i++){
      dataReceive[i] = 0;
    }
    while(Serial.available()){
        dataReceive[n++] = Serial.read();
    }  
//    for(int i=0; i<sizeof(dataReceive); i++){
//      Serial.print (dataReceive[i]);Serial.print ("|");
//    }
//    Serial.println();
    
//    title = reader = tag = "";
//    flagContent = flagTitle = flagEnd = false;
//
//    for (int i = 0; i<sizeof(dataReceive); i++){
//        if (dataReceive[i] == '}'){
//            flagContent = false;
//            title = "";
//        }
//        if (flagContent){
//            if (title == "READER")
//                reader += (char)(dataReceive[i]);
//            else if (title == "TAG")
//                tag += (char)(dataReceive[i]);
//        }
//        if (dataReceive[i] == ':'){
//            flagTitle = false;
//            flagContent = true;
//        }
//        if (flagTitle){
//            title += (char)(dataReceive[i]);
//        }
//        if (dataReceive[i] == '{'){
//            flagTitle = true;
//            flagContent = false;
//        }
//        if (dataReceive[i] == '/'){
//            flagEnd = true;
//        }
//    }
//    if (flagEnd){
//        if(tag == "2"){
//            sendmessage(2, ++num2);
//        } else if(tag == "3"){
//            sendmessage(3, ++num3);
//        } else if(tag == "4"){
//            sendmessage(4, ++num4);
//        } else if(tag == "6"){
//            sendmessage(6, ++num6);
//        } else if(tag == "20"){
//            sendmessage(20, ++num20);
//        }
//    }
}

void setup() {
    Serial.begin (115200);
    delay (200);
    //Serial.setDebugOutput(1);

    ConnectWifi();
    SetParameterAWS();

    Serial.println ("\nConnect MQTT:");
    if (connect ()){
        subscribe ();
    }
}

void loop() {
    //keep the mqtt up and running
    if (awsWSclient.connected ()) {   
        client->yield();
    } else {
        if (connect ()) //handle reconnection
          subscribe ();    
    }
    //sendmessage(2, ++num2);
    ReadSerial(); 
    delay(10);
}

