
const int EN_pin = 7;
const int DIR_pin = 8;
const int PWM_pin = 9; // Analog output pin that the LED is attached to
const int BUTTON_pin = 12;
const int ledPin =  13;

int outputValue = 0;        // value output to the PWM (analog out)
int last_buttonState = 0;
int buttonState = 0;
long last_debounce_time=0;
long debounce_delay=50;
bool flag_button = false;


void setup() {
  pinMode(EN_pin, OUTPUT);
  pinMode(DIR_pin, OUTPUT);
  pinMode(PWM_pin, OUTPUT);
  pinMode(BUTTON_pin, INPUT);
  pinMode(ledPin, OUTPUT);

  digitalWrite(BUTTON_pin,HIGH);
  last_buttonState = !digitalRead(BUTTON_pin);

  Control_motor(0, 0, 255);
}

void loop() {
  outputValue = 255;
  Check_button();
  if(flag_button == true)
  {
    digitalWrite(ledPin, buttonState);
  }
  
}

void Control_motor (int enable, int dir, int pwm)
{
  digitalWrite(EN_pin, HIGH);
  delay(10);
  digitalWrite(DIR_pin, LOW);
  analogWrite(PWM_pin, 255);}

void Check_button()
{
  buttonState = ! digitalRead(BUTTON_pin);
  
  if (last_buttonState != buttonState){
      last_debounce_time = millis();
  }
  
  //if the button value has not changed during the debounce delay
  // we know it is stable
  if ((millis() - last_debounce_time) > debounce_delay) {
    flag_button = ! flag_button;
  }

  last_buttonState = buttonState;
}

