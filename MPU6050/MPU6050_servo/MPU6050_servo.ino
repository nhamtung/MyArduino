/*
 * MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll & Yaw Gyroscope Example.
 * Arduino nano
 */
#include <Wire.h>
#include <Servo.h> 
#include "MPU6050.h"

MPU6050 mpu;
Servo myservo;  // khởi tạo đối tượng Servo với tên gọi là myservo // bạn có thể tạo tối đa 8 đối tượng Servo      

// Timers
unsigned long timer = 0;
float timeStep = 0.01;

// Pitch, Roll and Yaw values
float pitch = 0;
float roll = 0;
float yaw = 0;

unsigned int Angle;
unsigned int Angle_Old;

#define Led_MPU 10

void setup() 
{
  Serial.begin(115200);

  pinMode(Led_MPU, OUTPUT);
  digitalWrite(Led_MPU, LOW); 
  
  // Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();  // Calibrate gyroscope. The calibration must be at rest.
  mpu.setThreshold(3);  // Set threshold sensivty. Default 3.//*/

   
  myservo.attach(9);  // attach (đính) servo ở chân digital 9 // bạn có thể thay bằng bất cứ chân digital/analog nào khác
  myservo.write(90);              // xuất tọa độ ra cho servo
  //delay(5000); 
}

void loop()
{
  //servo();
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
  
  if (yaw < 0)
    Angle = (unsigned int)((yaw + 360)*100);
  else if (yaw >= 360)
    Angle = (unsigned int)((yaw - 360)*100);
  else Angle = (unsigned int)(yaw*100);
  Serial.print("A");Serial.print((Angle));Serial.println("/");//*/
  
  //Serial.print(" Pitch = ");Serial.print(pitch);  
  //Serial.print(" Roll = ");Serial.print(roll);  
  //Serial.print(" Yaw = ");Serial.println(yaw);
  
  delay((timeStep*1000) - (millis() - timer));  // Wait to full timeStep period//*/
  
  if(Angle == Angle_Old)
    digitalWrite(Led_MPU, LOW); 
  else digitalWrite(Led_MPU, HIGH); 
  Angle_Old = Angle;
}

void servo()
{
  for(int pos = 90; pos < 180; pos += 1)  // cho servo quay từ 0->179 độ
  {                                  // mỗi bước của vòng lặp tăng 1 độ
    myservo.write(pos);              // xuất tọa độ ra cho servo
    Read_MPU();
  } 
  delay(3000); 
  
  for(int pos = 180; pos > 45; pos --)     // cho servo quay từ 179-->0 độ
  {                                
    myservo.write(pos);              // xuất tọa độ ra cho servo
    Read_MPU();
  } //*/
  delay(3000); 
}
