#include <IRremote.h> // thư viện hỗ trợ IR remote

const int receiverPin = 8; // chân digital 8 dùng để đọc tín hiệu
IRrecv irrecv(receiverPin); // tạo đối tượng IRrecv mới
decode_results results;// lưu giữ kết quả giải mã tín hiệu

const int LED = 13;// LED đỏ
boolean stateLED = false;

String dataOff = "1317527723";  //Decema type
String dataOn = "1319256238";  //Decema type
String dataTimer = "489680886";  //Decema type
String dataSwing = "338831067";  //Decema type
String dataNatural = "3768077238";  //Decema type

void setup()
{
  Serial.begin(115200);// serial 
  irrecv.enableIRIn(); // start the IR receiver
  pinMode(LED, OUTPUT);
}
// translate IR signals
void translateIR()
{
  if((String(results.value) == dataOff) 
    || (String(results.value) == dataOn)
    || (String(results.value) == dataTimer)
    || (String(results.value) == dataSwing)
    || (String(results.value) == dataNatural))
  {
    stateLED = !stateLED;
    digitalWrite(LED, stateLED); 
  }
}
void loop()
{
  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  {
    translateIR();
    Serial.println(results.value, HEX);
    delay(200);
    irrecv.resume(); // nhận giá trị tiếp theo
  }
}
