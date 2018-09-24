/*
 * Sử dụng ESP8266 để tạo ra một web server nhỏ trên chip,
 * sao đó tạo ra giao diện web để có thể điều khiển đèn
 * https://hocarm.org/dieu-khien-den-hoc-qua-website-voi-esp8266/
 */
 
#include <ESP8266WiFi.h>

// Thong so WiFi
const char* ssid = "CH3CHO + H2";  //Thay  ten_wifi bang ten wifi nha ban
const char* password = "ch3ch2oh"; //Thay mat_khau_wifi bang mat khau cua ban

WiFiServer server(80);// Tao server
int output_pin = 5;

void setup() 
{
  Serial.begin(115200);// Khoi dong serial de debug
  delay(10);
  
    // Khai bao GPIO5
  pinMode(output_pin, OUTPUT);
  digitalWrite(output_pin, 0);
  
// Ket noi voi WiFi  
  Serial.println();Serial.println();
  Serial.print("Dang ket noi toi mang ");Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)  //Kiem tra xem trang thai da ket noi chua neu chua thi in ra dau .
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  server.begin();  // Khoi dong server
  Serial.println("Khoi dong Server");
  
  Serial.println(WiFi.localIP());// Neu da ket noi duoc voi wifi se in ra dia chi IP
}

void loop() 
{
  // Kiem tra neu co client ket noi
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Doi client gui data
  Serial.println("Co client moi");
  while(!client.available())
  {
    delay(1);
  }

    // Doc yeu cau tu client
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Kiem tra yeu cau la gi
  if (req.indexOf("/on") != -1){
    digitalWrite(output_pin, 1);
  }
  else if (req.indexOf("/off") != -1) {
    digitalWrite(output_pin, 0);
  }

  client.flush();

  // Chuan bi thong tin phan hoi
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  s += "<head>";
  s += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">";
  s += "<script src=\"https://code.jquery.com/jquery-2.1.3.min.js\"></script>";
  s += "<link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.4/css/bootstrap.min.css\">";
  s += "</head>";
  s += "<div class=\"container\">";
  s += "<h1>Dieu khien den</h1>";
  s += "<div class=\"row\">";
  s += "<div class=\"col-md-2\"><input class=\"btn btn-block btn-lg btn-primary\" type=\"button\" value=\"On\" onclick=\"on()\"></div>";
  s += "<div class=\"col-md-2\"><input class=\"btn btn-block btn-lg btn-danger\" type=\"button\" value=\"Off\" onclick=\"off()\"></div>";
  s += "</div></div>";
  s += "<script>function on() {$.get(\"/on\");}</script>";
  s += "<script>function off() {$.get(\"/off\");}</script>";

  // Gui thong tin cho client
  client.print(s);
  delay(1);
  Serial.println("Ngat ket noi Client");
}
