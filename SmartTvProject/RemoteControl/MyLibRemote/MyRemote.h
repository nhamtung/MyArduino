
#ifndef MyRemote_h
#define MyRemote_h

#include "Arduino.h"
#include "IRremote.h"

class MyRemote
{
  public:
    MyRemote(long SERIAL_BAURATE);
    void sendCode(int repeat);
    void storeCode(decode_results *results);
  private:
    IRsend irsend;
    decode_results results;
    
    	// Storage for the recorded code
  	int codeType = -1; // The type of code
  	unsigned long codeValue; // The code value if not raw
  	unsigned int rawCodes[RAWBUF]; // The durations if raw
  	int codeLen; // The length of the code
  	int toggle = 0; // The RC5/6 toggle state
};
#endif
