// http://hocdientu.vn/threads/%C4%90o-d%C3%B2ng-dc-v%C3%A0-ac-d%C3%B9ng-acs712-v%C3%A0-arduino.8287/#post-28380
// PIN A0

#include <Wire.h>
#include "SimpleKalmanFilter.h" 

#define CURRENT_SENSOR A7  
SimpleKalmanFilter simpleKalmanFilter(1, 1, 0.01);

void setup() {
    pinMode(CURRENT_SENSOR,INPUT);
    Serial.begin(115200);
}

void loop() {
  unsigned int irms = Irms();
}

unsigned int Irms(){
    int valueMax=512;
    int valueMin=1023;
    int value, adc1, adc2, adc;
    unsigned int i;
    for(int i ; i<1000;i++){
        value=analogRead(CURRENT_SENSOR);  
        if(value>valueMax){
            valueMax=value;}
        if(value<valueMin){
            valueMin=value; }
    }
    
    adc1 = abs(valueMax-512);
    adc2 = abs(512-valueMin);
    adc = (adc1+adc2)/2;
    if(adc1 == 0){
      Serial.println(F("ERROR: Can't connect VCC or Analog pin to ACS712!"));
    }else if(adc1 == 511){
      Serial.println(F("ERROR: Can't connect GND pin to ACS712!"));
    }else{
      i = adc * 5;
    }

    Serial.print(F("\tadc1"));Serial.print(F("\tadc2"));Serial.print(F("\tadc"));Serial.println(F("\tI"));
    Serial.print(F("\t"));Serial.print(adc1);
    Serial.print(F("\t"));Serial.print(adc2);  
    Serial.print(F("\t"));Serial.print(adc);  
    Serial.print(F("\t"));Serial.println(i);  
        
    float kal_i = simpleKalmanFilter.updateEstimate(i);
    
//    Serial.print(i);
//    Serial.print(",");
//    Serial.print(kal_i,4);
//    Serial.println();

    return kal_i;
}

