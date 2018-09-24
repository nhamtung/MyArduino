/*
 * Sizeof(array) trả về tổng số byte bộ nhớ trong mảng
 * example: 
 *    - Khai bào mảng: int YF[] = {110,110};
 *    mảng có 2 phần tử, mỗi phần tử chiếm 2 byte bộ nhớ => sizeo(YF) = 4
 *    - Khai báo mang: float YF[] = {110,110};
 *    Mang có 2 phần tử, mỗi phần tử chiếm 4 byte bộ nhớ => sizeof(YF) = 8
 */
 
int YF[] = {110,110};//*/

void setup() 
{
  Serial.begin(115200);
  for(int i=0; i < sizeof(YF)/2; i++)
  {
    Serial.print("i = ");Serial.print(i);
    Serial.print("     YF = ");Serial.println(YF[i]);
  }
  Serial.print("Size = ");Serial.println(sizeof(YF)/2);
}

void loop() {
  // put your main code here, to run repeatedly:

}
