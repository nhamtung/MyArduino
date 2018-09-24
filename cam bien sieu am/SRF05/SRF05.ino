//ARDUINO MEGA2560

#define trig 10
#define echo 11
void setup()
{
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  Serial.begin(115200);
}
void loop()
{
  Serial.print(objectDistance_mm());
  Serial.println("mm");
  delay(100); 
}
int objectDistance_mm()
{
  unsigned long thoigian;
  int distance;
  
  /*Phat xung tu chan Trig*/
  digitalWrite(trig,0);
  delayMicroseconds(2);
  digitalWrite(trig,1);
  delayMicroseconds(5);
  digitalWrite(trig,0);
  
  /*Tinh toan*/
  thoigian = pulseIn(echo,1);  //ms
  distance = int((thoigian/2)/2.94117647);  //1/2.94117647 m/ms : van toc song sieu am
  return distance;
}
