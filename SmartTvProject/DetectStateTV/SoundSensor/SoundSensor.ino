#include "SimpleKalmanFilter.h" 

SimpleKalmanFilter simpleKalmanFilter(1, 1, 0.5);

// Serial output refresh time
const long SERIAL_REFRESH_TIME = 2000;
long refresh_time;

double val = 0;
double pre_val = 0;

float delta = 0;
int num = 0;
boolean ledStatus = 1;
int i = 0;

uint32_t timer;

void setup()
{
    Serial.begin(115200);
  
    pinMode(A0, INPUT);
    pinMode(13, OUTPUT);
    
    timer = micros();
}

void loop()
{
    val = analogRead(A0);
    float kal_val = simpleKalmanFilter.updateEstimate(val);

    delta = abs(kal_val - pre_val);
    if (delta >= 0.4) num = 1;
    else num = 0;
    
    if(num) 
    {
      ledStatus = 1;
      refresh_time = millis() + SERIAL_REFRESH_TIME;
    }
    else
      if (millis() > refresh_time) {   
          ledStatus = 0;
          num = 0;
          refresh_time = millis() + SERIAL_REFRESH_TIME;
      }    
      
    pre_val = kal_val;
    
    Serial.print(delta);
    Serial.print(",");
    Serial.print(val);
    Serial.print(",");
    Serial.print(kal_val,1);
    Serial.println();
    
    digitalWrite(13, ledStatus);
}

