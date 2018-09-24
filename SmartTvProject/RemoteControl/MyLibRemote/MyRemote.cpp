
#include "Arduino.h"
#include "MyRemote.h"
#include "IRremote.h"

MyRemote::MyRemote(long SERIAL_BAURATE)
{
    Serial.begin(SERIAL_BAURATE);
}

// Stores the code for later playback
// Most of this code is just logging
void MyRemote::storeCode(decode_results *results) {
  codeType = results->decode_type;
  //int count = results->rawlen;
  if (codeType == UNKNOWN) {
      Serial.println("Received unknown code, saving as raw");
      codeLen = results->rawlen - 1;
      // To store raw codes:
      // Drop first value (gap)
      // Convert from ticks to microseconds
      // Tweak marks shorter, and spaces longer to cancel out IR receiver distortion
      for (int i = 1; i <= codeLen; i++) {
        if (i % 2) {
          rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK - MARK_EXCESS; // Mark
          //Serial.print(" m");
        } 
        else {
          rawCodes[i - 1] = results->rawbuf[i]*USECPERTICK + MARK_EXCESS; // Space
          //Serial.print(" s");
        }
        //Serial.print(rawCodes[i - 1], HEX);
      }
      Serial.println("");
  
      Serial.print("codeLen: "); Serial.println(codeLen);
      for(int i=1; i<=codeLen; i++){
        Serial.print(rawCodes[i - 1], HEX); Serial.print(", "); 
      }
      Serial.println("\n");
  }
  else {
      if (codeType == NEC) {
        Serial.println("Received NEC: ");
        if (results->value == REPEAT) {
          // Don't record a NEC repeat value as that's useless.
          Serial.println("repeat; ignoring.");
          return;
        }
      } 
      else if (codeType == SONY) {
        Serial.println("Received SONY: ");
      } 
      else if (codeType == RC5) {
        Serial.println("Received RC5: ");
      } 
      else if (codeType == RC6) {
        Serial.println("Received RC6: ");
      } 
      else if (codeType == DISH) {
        Serial.println("Received DISH: ");
      } 
      else if (codeType == SHARP) {
        Serial.println("Received SHARP: ");
      } 
      else if (codeType == PANASONIC) {
        Serial.println("Received PANASONIC: ");
      }
      else if (codeType == JVC) {
        Serial.println("Received JVC: ");
      }
      else if (codeType == SANYO) {
        Serial.println("Received SANYO: ");
      } 
      else if (codeType == MITSUBISHI) {
        Serial.println("Received MITSUBISHI: ");
      } 
      else if (codeType == SAMSUNG) {
        Serial.println("Received SAMSUNG: ");
      } 
      else if (codeType == LG) {
        Serial.println("Received LG: ");
      } 
      else {
        Serial.print("Unexpected codeType: "); Serial.println(codeType, DEC);
      }
      codeValue = results->value;
      codeLen = results->bits;
      Serial.print("Received value: ");Serial.println(codeValue, HEX);
      Serial.print("codeLen: ");Serial.println(codeLen);
    }
}

void MyRemote::sendCode(int repeat) {
  if (codeType == NEC) {
      if (repeat) {
        irsend.sendNEC(REPEAT, codeLen);
        Serial.println("Sent NEC repeat");
      } 
      else {
        irsend.sendNEC(codeValue, codeLen);
        Serial.print("Sent NEC ");
        Serial.println(codeValue, HEX);
      }
  } 
  else if (codeType == SONY) {
      irsend.sendSony(codeValue, codeLen);
      Serial.print("Sent Sony ");
      Serial.println(codeValue, HEX);
  } 
  else if (codeType == PANASONIC) {
      irsend.sendPanasonic(codeValue, codeLen);
      Serial.print("Sent Panasonic");
      Serial.println(codeValue, HEX);
  }
  else if (codeType == JVC) {
      irsend.sendJVC(codeValue, codeLen, false);
      Serial.print("Sent JVC");
      Serial.println(codeValue, HEX);
  }
  else if (codeType == DISH) {
      irsend.sendDISH(codeValue, codeLen);
      Serial.print("Sent DISH");
      Serial.println(codeValue, HEX);
  }
  else if (codeType == SHARP) {
      irsend.sendSharp(codeValue, codeLen);
      Serial.print("Sent SHARP");
      Serial.println(codeValue, HEX);
  }
  else if (codeType == SAMSUNG) {
      irsend.sendSAMSUNG(codeValue, codeLen);
      Serial.print("Sent SAMSUNG");
      Serial.println(codeValue, HEX);
  }
  else if (codeType == RC5 || codeType == RC6) {
      if (!repeat) {
        toggle = 1 - toggle; // Flip the toggle bit for a new button press
      }
      // Put the toggle bit into the code to send
      codeValue = codeValue & ~(1 << (codeLen - 1));
      codeValue = codeValue | (toggle << (codeLen - 1));
      if (codeType == RC5) {
        Serial.print("Sent RC5 ");
        Serial.println(codeValue, HEX);
        irsend.sendRC5(codeValue, codeLen);
      } 
      else {
        irsend.sendRC6(codeValue, codeLen);
        Serial.print("Sent RC6 ");
        Serial.println(codeValue, HEX);
      }
  } 
  else if (codeType == UNKNOWN /* i.e. raw */) {
      irsend.sendRaw(rawCodes, codeLen, 38);    // Assume 38 KHz
      Serial.print("codeLen: "); Serial.println(codeLen);
      Serial.print("sendRaw: ");
      for(int i=1; i<=codeLen; i++){
        Serial.print(rawCodes[i - 1], HEX);Serial.print(", ");
      }
      Serial.println("\n");
  }
}
