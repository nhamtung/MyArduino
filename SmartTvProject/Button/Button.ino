/*
 * Arduino Nano
 * 
 *  Button: PIN 2 (D2) 
 */
 
const int buttonPin = 2;     // the number of the pushbutton pin

void setup() {
    Serial.begin(115200);
    pinMode(buttonPin, INPUT);
}

void loop() {
    if(digitalRead(buttonPin) == 0)
        Serial.println("ON");
    else
        Serial.println("OFF");
}
