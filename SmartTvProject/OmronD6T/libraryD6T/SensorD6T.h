
#ifndef SensorD6T_h
#define SensorD6T_h

#include "Arduino.h"

class SensorD6T
{
  public:
    SensorD6T(byte COUNT, byte DATA);
    bool DetectHuman();
    unsigned int t_PTAT;
    unsigned int tdata[16];
    
  private:
    bool D6T_checkPEC(byte buf[] , byte pPEC );
    unsigned char Calc_crc(unsigned char data);
    
    byte count;
    byte data;
    byte rbuf[];
};
#endif
