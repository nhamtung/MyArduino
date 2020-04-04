
const byte interruptModePin = 3;
const byte switchMode = 5;
int countINT = 0;
volatile byte stateMode = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptModePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptModePin), buttonClick, FALLING);
  
  Serial.println("READY");
}

void loop() {
  if(countINT >= 1) {
    stateMode = !stateMode;
  }
  digitalWrite(switchMode, stateMode);
  countINT = 0;
  delay(1000);
}

void buttonClick() {
  countINT++;
}
