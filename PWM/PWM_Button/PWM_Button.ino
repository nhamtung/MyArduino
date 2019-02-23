
const int buttonPin = 12; 
int buttonState = 0; 
int pwm_value = 0;

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  pinMode(9, OUTPUT);   // sets the pin as output
  pinMode(8, OUTPUT);
}

void loop()
{
  buttonState = digitalRead(buttonPin);
  if(buttonState == HIGH){
    pwm_value = 100;
    digitalWrite(13, HIGH);
  }
  else {
    pwm_value = 255;
    digitalWrite(13, LOW);
  }
    
  digitalWrite(8, HIGH);
  analogWrite(9,pwm_value);  // analogRead values go from 0 to 1023, analogWrite values from 0 to 255
}
