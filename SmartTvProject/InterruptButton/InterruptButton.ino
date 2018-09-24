#define LED_ENABLE A2
#define LED_SETUP A3
#define BUTTON 2

volatile byte buttonState = HIGH;

void setup() {
    Serial.begin(115200);
    
    pinMode(LED_ENABLE, OUTPUT);
    digitalWrite(LED_ENABLE, HIGH);
    pinMode(LED_SETUP, OUTPUT);
    digitalWrite(LED_SETUP, LOW);
    
    pinMode(BUTTON, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BUTTON), blink, LOW);
}

void loop() {
    Serial.println(buttonState);
    if(buttonState == HIGH){
        digitalWrite(LED_ENABLE, HIGH);
    }else{
        digitalWrite(LED_ENABLE, LOW);
    }
}

void blink() {
  buttonState = !buttonState;
}
