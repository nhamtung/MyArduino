
const int dataPin = 4;     // PIN D4
const int ledPin =  13;      // the number of the LED pin

void setup() {
    Serial.begin(115200);
  
    pinMode(dataPin, INPUT);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    Serial.println("Setup!");
}

void loop() {
    if (digitalRead(dataPin) == HIGH) {
        digitalWrite(ledPin, HIGH);
        Serial.println("MOVING!");
    } else {
        digitalWrite(ledPin, LOW);
        Serial.println("STOP!");
    }
}
