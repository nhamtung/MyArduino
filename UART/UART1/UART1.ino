/*
 *  Arduino Mega 2560
 */
 
int S1,S2,S3;
String Str = "";  

void setup() 
{
  Serial.begin(115200);
  Serial1.begin(115200);
  pinMode(13,OUTPUT);
}

void loop() 
{
  serial1_Event();
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(2000);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(3000);              // wait for a second */
}

void serial1_Event() 
{
  int i=0;
  char c=0;
  if(Serial1.available()) 
  {    
    while(c != 'S')
    {
      if (Serial1.available()) 
      {
        c = Serial1.read();
        if (isDigit(c))    //kiểm tra data[k] có là một ký tự số hay không
        Str += (char)c;    //ghép các kí tự số thành một chuỗi số   
      }
    }

    if((Str.toInt()%10) == 1)
    {
       S1 = Str.toInt()/10;  //chuyển đổi chuỗi số sang một số nguyên
       Serial.print("S1: ");Serial.println(S1);
    }
    if((Str.toInt()%10) == 2)
    {
       S2 = Str.toInt()/10;  //chuyển đổi chuỗi số sang một số nguyên
       Serial.print("S2: ");Serial.println(S2);
    }
    if((Str.toInt()%10) == 3)
    {
       S3 = Str.toInt()/10;  //chuyển đổi chuỗi số sang một số nguyên
       Serial.print("S3: ");Serial.println(S3);
    }
    Str = "";
  }
}
