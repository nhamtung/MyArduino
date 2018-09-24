/*
 * MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll & Yaw Gyroscope Example.
 * Arduino nano
 */
#include <Wire.h>
#include "MPU6050.h"

MPU6050 mpu;

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

unsigned int Angle;

void setup() 
{
  Serial.begin(115200);

  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();  // Calibrate gyroscope. The calibration must be at rest.
  mpu.setThreshold(3);  // Set threshold sensivty. Default 3.//*/
}

void loop()
{
    Read_MPU();
}

void Read_MPU()
{
  timer = millis();

  Vector norm = mpu.readNormalizeGyro();  // Read normalized values

  // Calculate Pitch, Roll and Yaw
  //pitch = pitch + norm.YAxis * timeStep;
  //roll = roll + norm.XAxis * timeStep;
  yaw = yaw + norm.ZAxis * timeStep;    
  
/*  if (pitch < 0)
    Angle = (unsigned int)((pitch + 360)*100);
  else if (pitch >= 360)
    Angle = (unsigned int)((pitch - 360)*100);
  else Angle = (unsigned int)(pitch*100);
  Serial.print("A");Serial.print((Angle));Serial.println("/");//*/
  
  //Serial.print(" Pitch = ");Serial.print(pitch);  
  //Serial.print(" Roll = ");Serial.print(roll);  
  Serial.print(" Yaw = ");Serial.println(yaw);
  
  delay((timeStep*1000) - (millis() - timer));  // Wait to full timeStep period//*/
}
