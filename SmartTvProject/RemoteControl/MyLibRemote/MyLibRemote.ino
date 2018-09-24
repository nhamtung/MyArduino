/*
 * IRrecord: record and play back IR signals as a minimal 
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * An IR LED must be connected to the output PWM pin 3.
 * A button must be connected to the input BUTTON_PIN; this is the
 * send button.
 * A visible LED can be connected to STATUS_PIN to provide status.
 *
 * The logic is:
 * If the button is pressed, send the IR code.
 * If an IR code is received, record it.
 *
 * Version 0.11 September, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include "MyRemote.h"

int RECV_PIN = 8;
int BUTTON_PIN = 2;

IRrecv irrecv(RECV_PIN);
decode_results results;

#define SERIAL_BAURATE 115200
MyRemote myRemote(SERIAL_BAURATE);

int lastButtonState;

void setup()
{
    Serial.begin(SERIAL_BAURATE);
    pinMode(BUTTON_PIN, INPUT);
    irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  bool buttonState = digitalRead(BUTTON_PIN);
  if (!buttonState) {
    Serial.println("Pressed, sending");
    myRemote.sendCode(lastButtonState == buttonState);
    delay(50); // Wait a bit between retransmissions
    irrecv.enableIRIn(); // Re-enable receiver
  } 
  else {
    if (irrecv.decode(&results)) {
        myRemote.storeCode(&results);
        irrecv.resume(); // resume receiver
    }
  }
  lastButtonState = buttonState;
}
