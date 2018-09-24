/*
 * Cảm biến PIR xác định nhiệt chuyển động
 * Camr bieens VL53L0X xác định khoảng cách
 * 
 * PIN sersor PIR - PIN Arduino nano:
 * VCC - 5V
 * GND - GND
 * OUT - PIN D4
 * 
 * PIN Sensor VL53L0X - PIN Arduino Nano:
 * VCC - 5V 
 * GND - GND
 * SDA - PIN A4
 * SCL - PIN A5
 */
 
#include "Adafruit_VL53L0X.h"

Adafruit_VL53L0X lox = Adafruit_VL53L0X();

int ledPin = 13;        // chọn chân 13 báo hiệu LED
int inputPin = 4;       // chọn ngõ tín hiệu vào cho PIR
bool pirState = false;     // trạng thái ban đầu cảm biến PIR
bool vl53l0xState = false;
bool flagHuman = false;
String stateHuman = "";
int val = 0;
 
void setup(){
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}
 
void loop(){
    DetectHuman();
    Serial.println();
    delay(100);
}

void DetectHuman(){
  if(ReadSensorPIR() == true){
    if(ReadSensorVL53L0X() >= 300){
      stateHuman = "HUMAN";
      flagHuman = true;
    }
  }
  if(ReadSensorVL53L0X() < 300){
      stateHuman = "No HUMAN";
      flagHuman = false;
  }
  Serial.println(stateHuman);
}

bool ReadSensorPIR(){
  val = digitalRead(inputPin);    // đọc giá trị đầu vào.
 // Serial.println(val);
  if (val == HIGH){
    if (pirState == false){
 //     Serial.println("Motion detected!");
      pirState = true;
    }
  }else{
    if (pirState == true){
 //     Serial.println("Motion ended!");
      pirState = false;
    }
  } 
  return pirState;
}

int ReadSensorVL53L0X(){
  VL53L0X_RangingMeasurementData_t measure;
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

//  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
//    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
//  } else {
//    Serial.println(" out of range ");
//  }  
  return measure.RangeMilliMeter;
}

