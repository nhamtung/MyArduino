/*  MASTER
    The circuit: Arduino Uno (Schematic)
  * SS - to digital pin 10  (SS pin)   
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

char val;   
//int dataSend[5] = {0xBB, 0x02, 0x00, 0x04, 0x7E};
byte dataSend[5] = {0xBB, 0x02, 0x00, 0x06, 0x7E};

void setup() {
  Serial.begin (115200);
  
  pinMode(SS, OUTPUT);    // set the slaveSelectPin as an output:
  digitalWrite(SS, HIGH);
  SPI.begin();    // initialize SPI:
  SPI.setClockDivider(SPI_CLOCK_DIV8);   // Slow down the master a bit

}

void loop() {
  SendData();
}

void SendData(){
  Serial.print("\nSEND Data: ");
  //for (const char * p = "Hello, Boss!\n" ; val = *p; p++){
  for(int i=0; i<sizeof(dataSend); i++){
    Serial.print(dataSend[i]);
    SPI_Write(dataSend[i]); 
    Serial.print('|');
  }
  SPI_Write('/'); 
  delay(1000);
}
void SPI_Write( int value) {
  digitalWrite(SS, LOW);  // take the SS pin low to select the chip:
  SPI.transfer(value);
  digitalWrite(SS, HIGH);  // take the SS pin high to de-select the chip:
}
