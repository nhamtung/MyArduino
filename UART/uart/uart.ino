/*
 * arduino Uno
 */
int dataReceive;
char data[8] = {0xBB, 0x00, 0x22, 0x00, 0x00, 0x22, 0x7E};

void setup()
{
  Serial.begin(115200);
  pinMode(13,OUTPUT);
}

void loop()
{
  for(int i = 0; i < 7; i++)
  {
    Serial.print(data[i]);
  }
  
  if(Serial.available())
  {
    dataReceive = Serial.read();
    
/*    if(data=='1')
    {
      digitalWrite(13,HIGH);
    }
    if(data=='2')
    {
      digitalWrite(13,LOW);
    }
    
    if(data==0x43)
    {
      digitalWrite(13,HIGH);
    }
    if(data==0x44)
    {
      digitalWrite(13,LOW);
    }//*/
  }
  delay(1000);
}
