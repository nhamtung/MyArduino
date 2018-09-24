/*
 * Arduino nano
 */
#include <Servo.h>      // Thư viện điều khiển servo

int data,x,m=0;
int num[8];
int PES3=0,PES5=0;
int value;

Servo myservo;          
 
void setup ()
{
//    Serial.begin(9600); // Mở giao tiếp Serial ở baudrate 9600
    // Cài đặt chức năng điều khiển servo cho chân servoPin
    myservo.attach(8); 
    myservo.write(90);
    delay(500);

}
 
void loop ()
{
  if(Serial.available())
  {
    data = Serial.read();
    if(data=='@')  x=1;
    if(x==1)
    {
      num[m]=data-48;
      m++;
      if(m>7)
      {
        m=0;x=0;
      }
    }
    PES3=num[2]*100+num[3]*10+num[4];
    PES5=num[5]*100+num[6]*10+num[7];
  }
    value=PES3;
    int servoPos = map(value, 0, 255,30, 140);

    
    // Cho servo quay một góc là servoPos độ
    myservo.write(servoPos);
    
 //   Serial.println(servoPos);
    
//    delay(100);
}
