
#include "SimpleKalmanFilter.h"
SimpleKalmanFilter bo_loc(2, 2, 0.001);
 
float u0 = 100.0; // giá trị thực (không đổi)
float e; // nhiễu
float u; // giá trị đo được (có thêm nhiễu)
float u_kalman; // giá được lọc nhiễu
void setup()
{
    Serial.begin(115200);
}
void loop()
{
    randomSeed(millis());
    e = (float)random(-10, 10);
    u = u0 + e;
    Serial.print(u);
    Serial.print(",");
    u_kalman = bo_loc.updateEstimate(u); // tầng 1
    u_kalman = bo_loc.updateEstimate(u_kalman); // tầng 2
    u_kalman = bo_loc.updateEstimate(u_kalman); // tầng 3
    u_kalman = bo_loc.updateEstimate(u_kalman); // tầng 4
    Serial.println(u_kalman);
}
