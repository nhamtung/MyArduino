
#include "Arduino.h"
#include "SensorD6T.h"
#include <Wire.h>
#include "WireExt.h"

SensorD6T::SensorD6T(byte COUNT, byte DATA)
{
    Wire.begin(0x0A);  
    count = COUNT;
    data = DATA;
}

// Đọc giá trị cảm biến thân nhiệt
bool SensorD6T::DetectHuman() {
    // Begin a regular i2c transmission. Send the device address and then send it a command.
    Wire.beginTransmission(0x0A);
    Wire.write(0x4C);
    Wire.endTransmission();
    delay(70);
    
     // This is where things are handled differently. Omron D6T output data is 35 bytes and there is a limit here on what Wire can receive. We use WireExt to read the output data 1 piece at a time. We store each byte as an element in rbuf.
    if (WireExt.beginReception(0x0A) >= 0) {
        for (byte i = 0; i < count; i++) {
            rbuf[i] = WireExt.get_byte();
        }
        WireExt.endReception();  // end the reception routine
        t_PTAT = (rbuf[0]+(rbuf[1]<<8)); // Do something with temperature compensation that we don't seem to use currently.

        // Calculate the temperature values: add the low temp and the bit shifted high value together. Multiply by 0.1
        for (byte i =0; i<data; i++) {
            tdata[i]=(rbuf[(i*2+2)]+(rbuf[(i*2+3)]<<8));
        } 
        if(!D6T_checkPEC(rbuf, count-1))
            return false;
    }else return false;
    return true;
}

bool SensorD6T::D6T_checkPEC(byte buf[] , byte pPEC ){
    unsigned char crc;
    crc = Calc_crc(0x15);
    for(byte i=0; i<pPEC; i++){
        crc = Calc_crc( buf[i] ^ crc );
    }
    if (crc == buf[pPEC])
        return true;
    else return false;
}

unsigned char SensorD6T::Calc_crc(unsigned char data){
    int index;
    unsigned char temp;

    for(index = 0; index < 8; index++){
        temp = data;
        data <<= 1;
        if(temp & 0x80) data ^= 0x07;
    }
    return data;
}
