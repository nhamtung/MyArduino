/*
 * IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
 * An IR LED must be connected to Arduino PWM pin 3.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */

#include "IRremote.h"

IRsend irsend;

void setup()
{
  Serial.begin(115200);
}

void loop() {
    for(byte i=0; i<5; i++){
        irsend.sendSony(0xa90, 12); // Sony TV power code
        delay(40);
    }
    Serial.println(0xa90);
    delay(5000);
}
