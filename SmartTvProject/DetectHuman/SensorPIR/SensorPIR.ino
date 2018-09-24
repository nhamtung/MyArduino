/*
 * Cảm biến PIR xác định nhiệt chuyển động
 * PIN sersor - PIN Arduino nano:
 * VCC - 5V
 * GND - GND
 * OUT - PIN D4
 */
 
int ledPin = 13;        // chọn chân 13 báo hiệu LED
int inputPin = 4;       // chọn ngõ tín hiệu vào cho PIR
int pirState = LOW;     // Bắt đầu với không có báo động
int val = 0;
 
void setup(){
  pinMode(ledPin, OUTPUT);
  pinMode(inputPin, INPUT);
  Serial.begin(115200);

  Serial.println("Ready!");
}
 
void loop(){
    ReadSensorPIR();
    delay(100);
}

void ReadSensorPIR(){
  val = digitalRead(inputPin);    // đọc giá trị đầu vào.
  Serial.println(val);
  if (val == HIGH){
    if (pirState == LOW){
      Serial.println("Motion detected!");
      pirState = HIGH;
    }
  }else{
    if (pirState == HIGH){
      Serial.println("Motion ended!");
      pirState = LOW;
    }
  } 
}

