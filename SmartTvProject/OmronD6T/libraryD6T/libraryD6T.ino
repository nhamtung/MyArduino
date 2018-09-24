#include "SensorD6T.h"

#define SERIAL_BAURATE 115200

// define parameter for D6T44L06 sensor
#define COUNT 35
#define DATA 16
// define parameter for D6T8L09 sensor
//#define COUNT 19
//#define DATA 8
SensorD6T sensorD6T(COUNT, DATA);

bool flagHuman = false;
int8_t deltaFlagHuman = 0;
unsigned int countHuman = 0;
String stringHuman = "NO MAN";
int detalReferenceTemp = 0;

float tdata[DATA]; 
float t_PTAT;

void setup() {
    Serial.begin(SERIAL_BAURATE);
    while(!GetReferenceDegrees()){}

    Serial.println(F("\nReady!\n"));
}

void loop() {
  DetectHuman();
  ShowParameter();
  delay(100);
}

void DetectHuman() {
  if (sensorD6T.DetectHuman()) {
    DisplayTemperature(sensorD6T.t_PTAT, sensorD6T.tdata);
    byte countFlagHuman = 0;
    for (byte i = 0; i < DATA; i++) {
      if ((sensorD6T.tdata[i] > (sensorD6T.t_PTAT + detalReferenceTemp)) && (sensorD6T.tdata[i] < (sensorD6T.t_PTAT + detalReferenceTemp) + 60))
        countFlagHuman ++;
    }
    deltaFlagHuman = int8_t(countFlagHuman - GetFlagHuman(sensorD6T.t_PTAT));
    if (deltaFlagHuman > 0)
      countHuman++;
    else if (deltaFlagHuman < 0)
      countHuman = 0;
    if (countHuman > 10)
      flagHuman = true;
    else if (countHuman == 0)
      flagHuman = false;
    if (flagHuman)
      stringHuman = "MAN";
    else
      stringHuman = "NO MAN";
    //        Serial.print(F("countFlagHuman : ")); Serial.println(countFlagHuman);Serial.println();
  } else {
    Serial.println(F("\t\t\t ERROR: DetectHuman \n"));
  }
}
bool GetReferenceDegrees(){
  if (sensorD6T.DetectHuman()) {
    DisplayTemperature(sensorD6T.t_PTAT, sensorD6T.tdata);
    int maxValue = sensorD6T.tdata[0];
    for(byte i=0; i<DATA; i++){
      if(maxValue < sensorD6T.tdata[i]){
        maxValue = sensorD6T.tdata[i];
      }
    }
    detalReferenceTemp = maxValue - sensorD6T.t_PTAT;
    Serial.print(F("maxValue: "));Serial.println(maxValue);
    Serial.print(F("detalReference: "));Serial.println(detalReferenceTemp);
  }else {
    Serial.println(F("\t\t\t ERROR: DetectHuman \n"));
    return false;
  }
  return true;
}
// Hiển thị mảng dữ liệu của cảm biến thân nhiệt
void DisplayTemperature(unsigned int t_PTAT, unsigned int tdata[]) {
//  Serial.print(F("Temp(1=0.1 grad): ")); Serial.println(t_PTAT);
  Serial.print(F("Reference Temp: ")); Serial.println(t_PTAT + detalReferenceTemp);
  for (int i = 0; i < (byte)DATA; i++) {
    Serial.print(tdata[i]);
    Serial.print(F(", "));
  }
  Serial.println();
}
byte GetFlagHuman(unsigned int t_PTAT) {
  byte flagHuman = 2;
//  if (t_PTAT <= 230)
//    flagHuman = 3;
//  if ((t_PTAT > 230) && (t_PTAT <= 250))
//    flagHuman = 3 ;
//  if ((t_PTAT > 250) && (t_PTAT <= 270))
//    flagHuman = 2;
//  if ((t_PTAT > 270) && (t_PTAT <= 290))
//    flagHuman = 2;
//  if ((t_PTAT > 290) && (t_PTAT <= 310))
//    flagHuman = 3;
//  if ((t_PTAT > 310) && (t_PTAT <= 330))
//    flagHuman = 5;
//  if (t_PTAT > 330)
//    flagHuman = 6;
  return flagHuman;
}
void ShowParameter() {
  Serial.print(F("\t")); Serial.print(stringHuman); Serial.print(F("\t")); 
  Serial.print(F("\t"));Serial.print(deltaFlagHuman); Serial.println(F("\t"));
}
