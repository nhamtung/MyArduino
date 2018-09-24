/* This example shows how to use continuous mode to take
range measurements with the VL53L0X. It is based on
vl53l0x_ContinuousRanging_Example.c from the VL53L0X API.

The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(100);

  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  sensor.startContinuous();
  Serial.println("\tREADY!");
}

void loop()
{
    Serial.println(sensor.readRangeContinuousMillimeters());
    if (sensor.timeoutOccurred()) { 
        Serial.println(" TIMEOUT");
    }
}
