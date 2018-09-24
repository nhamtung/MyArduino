/* record.ino Example sketch for IRLib2
 *  Illustrate how to record a signal and then play it back.
 */
#include <IRLibDecodeBase.h>  //We need both the coding and
#include <IRLibSendBase.h>    // sending base classes
#include <IRLib_P01_NEC.h>    //Lowest numbered protocol 1st
#include <IRLib_P02_Sony.h>   // Include only protocols you want
#include <IRLib_P03_RC5.h>
#include <IRLib_P04_RC6.h>
#include <IRLib_P05_Panasonic_Old.h>
#include <IRLib_P07_NECx.h>
#include <IRLib_HashRaw.h>    //We need this for IRsendRaw
#include <IRLibCombo.h>       // After all protocols, include this
// All of the above automatically creates a universal decoder
// class called "IRdecode" and a universal sender class "IRsend"
// containing only the protocols you want.
// Now declare instances of the decoder and the sender.
IRdecode myDecoder;
IRsend mySender;

#define BUTTON 2

// https://os.mbed.com/users/yuhki50/code/IRremote/rev/70c8e56bac45/
#define SONY_POWER      0xA90
#define SAMSUNG_POWER   0xE0E040BF
#define SHARP_POWER     0x41A2
#define PANASONIC_POWER 0x100BCBD
#define NEC_POWER       0x61a0f00f

// Include a receiver either this or IRLibRecvPCI or IRLibRecvLoop
#include <IRLibRecv.h>
IRrecv myReceiver(8); //pin number for the receiver

// Storage for the recorded code
uint8_t codeProtocol;  // The type of code
uint32_t codeValue;    // The data bits if type is not raw
uint8_t codeBits;      // The length of the code in bits

//These flags keep track of whether we received the first code 
//and if we have have received a new different code from a previous one.
bool gotOne, gotNew; 

void setup() {
  gotOne=false; gotNew=false;
  codeProtocol=UNKNOWN; 
  codeValue=0; 
  Serial.begin(115200);
  delay(1000);while(!Serial);//delay for Leonardo

  myReceiver.enableIRIn(); // Start the receiver
  
  pinMode(BUTTON, INPUT);
}

// Stores the code for later playback
void storeCode(void) {
  gotNew=true;    gotOne=true;
  codeProtocol = myDecoder.protocolNum;
  Serial.print(F("Received: ")); Serial.println(Pnames(codeProtocol));
  
  if (codeProtocol==UNKNOWN) {
    Serial.println(F(" saving raw data."));
    myDecoder.dumpResults();
    codeValue = myDecoder.value;
  }
  else {
    if (myDecoder.value == REPEAT_CODE) {
      // Don't record a NEC repeat value as that's useless.
      Serial.println(F("repeat; ignoring."));
    } else {
      codeValue = myDecoder.value;
      codeBits = myDecoder.bits;
    }
    Serial.print(F(" Value:0x"));
    Serial.println(codeValue, HEX);
  }
}
void sendCode(void) {
//  if( !gotNew ) {//We've already sent this so handle toggle bits
//    if (codeProtocol == RC5) {
//      codeValue ^= 0x0800;
//    }
//    else if (codeProtocol == RC6) {
//      switch(codeBits) {
//        case 20: codeValue ^= 0x10000; break;
//        case 24: codeValue ^= 0x100000; break;
//        case 28: codeValue ^= 0x1000000; break;
//        case 32: codeValue ^= 0x8000; break;
//      }      
//    }
//  }
//  gotNew=false;
  if(codeProtocol== UNKNOWN) {
    //The raw time values start in decodeBuffer[1] because
    //the [0] entry is the gap between frames. The address
    //is passed to the raw send routine.
    codeValue=(uint32_t)&(recvGlobal.decodeBuffer[1]);
    //This isn't really number of bits. It's the number of entries
    //in the buffer.
    codeBits=recvGlobal.decodeLength-1;
  }
  codeProtocol = SHARP;
  codeValue = SHARP_POWER;
  codeBits = 15;
  mySender.send(codeProtocol,codeValue,codeBits);
  
  Serial.print(F("Sent: ")); Serial.println(Pnames(codeProtocol));
  Serial.print(F(" Value:0x")); Serial.println(codeValue, HEX);
  Serial.print(F(" codeBits: ")); Serial.println(codeBits);
}

void loop() {
  if(digitalRead(BUTTON)){
    if (myReceiver.getResults()) {
      Serial.println("myReceiver.getResults()");
      myDecoder.decode();
      storeCode();
      myReceiver.enableIRIn(); // Re-enable receiver
    }
  }
  else{
    sendCode();
    delay(1000);
    myReceiver.enableIRIn(); // Re-enable receiver
  }
}

