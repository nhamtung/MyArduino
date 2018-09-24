
#ifndef LedBlink_h
#define LedBlink_h

#include "Arduino.h"
class Morse
{
  public:
    Morse(int pin);
    void dot();
    void dash();
  private:
    int _pin;
};
#endif
