// EmonLibrary examples openenergymonitor.org, Licence GNU GPL V3
// Data PIN: A0 - Arduino Nano

// http://www.homautomation.org/2013/09/17/current-monitoring-with-non-invasive-sensor-and-arduino/

#include "EmonLib.h"                   // Include Emon Library
EnergyMonitor emon1;                   // Create an instance
 
void setup()
{  
  Serial.begin(115200);
 
  emon1.current(0, 11.288);             // Current: input pin, calibration.
  //calibration is explained bellow
}
 
void loop()
{
  double Irms = emon1.calcIrms(500);  // the number of sample used to compute a value
  Serial.print(Irms*1000); //mA 
  Serial.println(); 
}

// calibration_value = ( i(measured) / i(sensor) ) / R(burden)
// i(measured) = √2 * i(rms_current) = 1.414 * 20A = 28.22 A
// i(sensor) = i(measured) / nb_turns = 28.22A / 2000 = 0.01411 A
// R(burden) = U(sensor)/I(sensor) = 2.5V / 0.01411A = 177.1793Ω
// calibration_value = (28.22 A /  0.01411A) / 177.1793Ω  = 11.288




