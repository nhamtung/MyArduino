 #include "IRremote.h" // thư viện hỗ trợ IR remote

const int receiverPin = 8; // chân digital (D8) dùng để đọc tín hiệu
IRrecv irrecv(receiverPin); // tạo đối tượng IRrecv mới
decode_results results;// lưu giữ kết quả giải mã tín hiệu

long rec = 0;

void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn(); // start the IR receiver
}
void loop()
{
  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  {
    rec = results.value;
    Serial.print("IR Hex: ");Serial.print(rec, HEX); // in ra Serial Monitor
    Serial.print("\t\tIR Dec: ");Serial.println(rec);
    Serial.println();
    delay(10);
    irrecv.resume(); // nhận giá trị tiếp theo
  }
}

