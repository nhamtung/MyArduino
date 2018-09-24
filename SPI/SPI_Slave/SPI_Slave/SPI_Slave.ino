
/*   SLAVE
        The circuit: Arduino Uno (Schematic)
  * CS - to digital pin 10  (SS pin)   
  * MOSI - to digital pin 11 (MOSI pin)
  * MISO - to digital pin 12 (MISO Pin)
  * CLK - to digital pin 13 (SCK pin)
  * 
    The circuit: Arduino Mega2560 (Schematic)
  * CS - to digital pin 53  (SS pin)
  * MOSI - to digital pin 51 (MOSI pin)
  * MISO - to digital pin 50 (MISO Pin)
  * CLK - to digital pin 52 (SCK pin)
  * 
    The circuit: Arduino Nano (Schematic)
  * SS - to digital pin 10  (SS pin)
  * MOSI - to digital pin 11 (MOSI pin)
  * MISO - to digital pin 12 (MISO Pin)
  * CLK - to digital pin 13 (SCK pin)
*/

#include <SPI.h>

char dataReceive [100];
volatile byte pos;
volatile bool check;

void setup() {
  Serial.begin (115200);

  SPCR |= bit (SPE);   // turn on SPI in slave mode
  pinMode (MISO, OUTPUT);   // have to send on master in, *slave out*
  pos = 0;   
  check = false;
  SPI.attachInterrupt();   // turn on interrupts
}

void loop() {
  CheckData();
}

void CheckData(){
    if (check == true){
    dataReceive [pos] = 0;
    if(dataReceive[0]){
      digitalWrite(13, !digitalRead(13));
      Serial.println("\nCHECK Data!\n");
    }     
    pos = 0;
    check = false;
  }
}

ISR (SPI_STC_vect){  // SPI interrupt routine
  byte c = SPDR;  // grab byte from SPI Data Register
  Serial.print (c);Serial.print ('|');
  
  if (pos < sizeof dataReceive){  // add to buffer if room
      dataReceive [pos++] = c;
      if (c == '/')     // example: newline means time to process buffer
        check = true;
    } 
}
