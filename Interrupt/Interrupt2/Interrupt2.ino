/*
 * interruptModePin on Arduino Nano is pin D2 and D3
 * Connect button to GND pin and interruptModePin
 */
 
const byte interruptModePin = 3;
const byte switchMode = 5;
const byte ledPin = 13;
const int timeWaitButtonMode = 500;

int countINT = 0;
volatile byte stateMode = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(switchMode, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptModePin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptModePin), buttonClick, FALLING);
  
  Serial.println("READY");
}

void loop() {
  if(countINT >= 1) {
    stateMode = !stateMode;
    Serial.println("Change Mode!");
  }
  digitalWrite(switchMode, stateMode);
  digitalWrite(ledPin, stateMode);
  countINT = 0;
  delay(timeWaitButtonMode);
}

void buttonClick() {
  countINT++;
  Serial.print("countINT: ");Serial.println(countINT);
}
