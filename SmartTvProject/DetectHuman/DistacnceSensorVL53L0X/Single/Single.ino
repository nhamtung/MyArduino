/* This example shows how to get single-shot range
 measurements from the VL53L0X. The sensor can optionally be
 configured with different ranging profiles, as described in
 the VL53L0X API user manual, to get better performance for
 a certain application. This code is based on the four
 "SingleRanging" examples in the VL53L0X API.

 The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

/* Uncomment this line to use long range mode. This
 increases the sensitivity of the sensor and extends its
 potential range, but increases the likelihood of getting
 an inaccurate reading because of reflections from objects
 other than the intended target. It works best in dark
 conditions. */
#define LONG_RANGE

// Uncomment ONE of these two lines to get
// - higher speed at the cost of lower accuracy OR
// - higher accuracy at the cost of lower speed
#define HIGH_SPEED
//#define HIGH_ACCURACY

void setup()
{
  Serial.begin(115200);
  Wire.begin();

  sensor.init();
  sensor.setTimeout(100);
  
  #if defined LONG_RANGE
      sensor.setSignalRateLimit(0.1);  // lower the return signal rate limit (default is 0.25 MCPS)
      // increase laser pulse periods (defaults are 14 and 10 PCLKs)
      sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
      sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
  #endif
  
  #if defined HIGH_SPEED
      sensor.setMeasurementTimingBudget(20000);  // reduce timing budget to 20 ms (default is about 33 ms)
  #elif defined HIGH_ACCURACY
      sensor.setMeasurementTimingBudget(200000);   // increase timing budget to 200 ms
  #endif

  Serial.println("READY");
}

void loop()
{
    Serial.println(sensor.readRangeSingleMillimeters());
    if (sensor.timeoutOccurred()) {
        Serial.println(" TIMEOUT"); 
    }
    delay(100);
}
