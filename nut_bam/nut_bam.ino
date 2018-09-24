const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin =  13;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
int currentState = 0;

void setup() 
{
  Serial.begin(115200);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  delay(5000);
}

void loop() 
{
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  Serial.println("gia tri cua currentState:");
  Serial.println(currentState);
  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
  if (buttonState == 1) 
  {
   Serial.println("NUT DUOC NHAN");
   if(currentState==1)
   {
    currentState=0;
   }
  else 
  {
   currentState=1;
  }
  digitalWrite(ledPin,currentState);
  delay(1000);
  }
}

