const byte ledPin = 13;
const byte interruptPin = 3;
volatile byte state = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), buttonClick, FALLING);
  Serial.println("READY");
}

void loop() {
  digitalWrite(ledPin, state);
}

void buttonClick() {
  delay(100);
  if(digitalRead(interruptPin) == 0) {
    state = !state;
    Serial.println("interrupt");
  }
}
