/*
 * Arduino Nano
 * Button: PIN 2 (D2) 
 * Read IR data: PIN 8 (D8)
 * Send IR Data: PIN 3 (D3)
 */
 
#include "IRremote.h"

const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

const int receiverIRdataPin = 8; // chân digital (D8) dùng để đọc tín hiệu

float powerCmd;
IRrecv irrecv(receiverIRdataPin); // tạo đối tượng IRrecv mới
decode_results results;// lưu giữ kết quả giải mã tín hiệu
IRsend irsend;

void setup() 
{
    Serial.begin(115200);
    irrecv.enableIRIn(); // start the IR receiver
  
    pinMode(ledPin, OUTPUT);
    pinMode(buttonPin, INPUT);
    Serial.println("READY!");
}

void loop() 
{
    if(digitalRead(buttonPin) == 1){
        ReadButtonState();
    }
    delay(10);
}

void ReadButtonState(){
    powerCmd = 0;
    irrecv.enableIRIn(); 
    while(digitalRead(buttonPin) == 1){        // read the state of the push button value
        ReadRemoteControl();
        delay(10);
    } 
    Serial.println(powerCmd);
    if(powerCmd != 0){
        Serial.println("Send Power Command");
        for(byte i=0; i<3; i++){
            irsend.sendSony(powerCmd, 12); // Sony TV power code
            delay(10);
        }
    }   
}

// Đọc tín hiệu từ Remote Control và điều khiển TV
void ReadRemoteControl(){
    if(irrecv.decode(&results)){
        Serial.println(results.value, HEX); // in ra Serial Monitor
        irrecv.resume(); // nhận giá trị tiếp theo
        powerCmd = results.value;
    }   
}



