#include <EasyDDNS.h>

#include <DHTesp.h>

#include <ESP8266WiFi.h>
const char* ssid = "Login3B"; //wifi SSID name
const char* pass = "xvxv1204"; //password
WiFiServer server(8369); //port

DHTesp dht;

#define D0 16
#define D1 5
#define D2 4
#define D6 12
/*#define D5 14
#define D7 13
*/
#define RIG1_ON_OFF D0
#define RIG2_ON_OFF D1
#define RIG3_ON_OFF D2
#define RIG4_ON_OFF D6
/*#define RIG1_CHK D5
#define RIG2_CHK D6
#define RIG3_CHK D7
*/

 /*int chkPWO1;
 int chkPWO2;
 int chkPWO3; 
*/
void setup () {
  Serial.begin(115200);
  pinMode(RIG1_ON_OFF, OUTPUT);
  pinMode(RIG2_ON_OFF, OUTPUT);
  pinMode(RIG3_ON_OFF, OUTPUT);
  pinMode(RIG4_ON_OFF, OUTPUT);
  /*pinMode(RIG1_CHK, INPUT_PULLUP);
  pinMode(RIG2_CHK, INPUT_PULLUP);
  pinMode(RIG3_CHK, INPUT_PULLUP);
  */
  digitalWrite(RIG1_ON_OFF, HIGH);
  digitalWrite(RIG2_ON_OFF, HIGH);
  digitalWrite(RIG3_ON_OFF, HIGH);
  digitalWrite(RIG4_ON_OFF, HIGH);

  dht.setup(14); // data pin 14
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  IPAddress local_ip = {192, 168, 1, 209};
  IPAddress gateway = {192, 168, 1, 1};
  IPAddress subnet = {255, 255, 255, 0};
  WiFi.config(local_ip, gateway, subnet);
  Serial.println("");
  Serial.println("Wi-Fi connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());
  server.begin();
  Serial.println("Server started");
  
  EasyDDNS.service("duckdns");    // Enter your DDNSName - "duckdns" / "noip"
  EasyDDNS.client("rigone.duckdns.org","095a65b4-ee15-4d6d-92df-b944f188ba8e"); //  Example - "esp.duckdns.org","1234567"
  
  }

/*void checkStatus(){
  chkPWO1 = digitalRead(RIG1_CHK);
  chkPWO2 = digitalRead(RIG2_CHK);
  chkPWO3 = digitalRead(RIG3_CHK);
  //if (!chkPWO1) 
}*/
void loop() {

  EasyDDNS.update(10000); // Check for New Ip Every 10 Seconds.
  
  // Check if a client has connected

  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  // Wait until the client sends some data
  //checkStatus();
  //Serial.println("new client");
  while (!client.available()) {
    delay(1);
  }
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  //Serial.println(request);
  client.flush();
  // Match the request
  //int value = LOW;
  if (request.indexOf("/RIG1=ON") != -1)  {
    digitalWrite(RIG1_ON_OFF, LOW);
    delay(500);
    digitalWrite(RIG1_ON_OFF, HIGH);
    //value = LOW;
    //checkStatus();
  }
   if (request.indexOf("/RIG2=ON") != -1)  {
    digitalWrite(RIG2_ON_OFF, LOW);
    delay(500);
    digitalWrite(RIG2_ON_OFF, HIGH);
  }
   if (request.indexOf("/RIG3=ON") != -1)  {
    digitalWrite(RIG3_ON_OFF, LOW);
    delay(500);
    digitalWrite(RIG3_ON_OFF, HIGH);
  }
   if (request.indexOf("/RIG4=ON") != -1)  {
    digitalWrite(RIG4_ON_OFF, LOW);
    delay(500);
    digitalWrite(RIG4_ON_OFF, HIGH);
  }
   if (request.indexOf("/RIG1=OFF") != -1)  {
    digitalWrite(RIG1_ON_OFF, LOW);
    delay(6000);
    digitalWrite(RIG1_ON_OFF, HIGH);
  }
   if (request.indexOf("/RIG2=OFF") != -1)  {
    digitalWrite(RIG2_ON_OFF, LOW);
    delay(6000);
    digitalWrite(RIG2_ON_OFF, HIGH);
  }
   if (request.indexOf("/RIG3=OFF") != -1)  {
    digitalWrite(RIG3_ON_OFF, LOW);
    delay(6000);
    digitalWrite(RIG3_ON_OFF, HIGH);
  }
   if (request.indexOf("/RIG4=OFF") != -1)  {
    digitalWrite(RIG4_ON_OFF, LOW);
    delay(6000);
    digitalWrite(RIG4_ON_OFF, HIGH);
  }
  /*if (request.indexOf("/RIG1=OFF") != -1)  {
    digitalWrite(RIG1_ON_OFF, HIGH);
    //checkStatus();
    //value = HIGH;
  }*/
  // Set ledPin according to the request
  //digitalWrite(ledPin, value)
  // Return the response

  // DHT Start here
  //Serial.println();
  delay(dht.getMinimumSamplingPeriod());
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<HTML><head>");
  client.println("<meta charset='utf-8'>");
  client.println("</head>");
  client.println("<br><br>");
  client.println("<h2>[ อุณหภูมิ : ");
  client.println(temperature);
  client.println(" *C ]");
  client.println("<br>");
  client.println("[ ความชื้น  : ");
  client.println(humidity);
  client.println(" % ]</h2>");
  
  /*if (chkPWO1 == LOW) {
    client.print("Off");
  } else {
    client.print("On");
   
  }*/
  client.print("RIG 1: ");
  client.println("<br><br>");
  client.println("<a href=\"/RIG1=ON\"\"><button>:: เปิด ::</button></a>");
  client.println("<a href=\"/RIG1=OFF\"\"><button>::  ปิด ::</button></a><br />");
  client.println("<br><br>");
  
  client.print("RIG 2: ");
  client.println("<br><br>");
  client.println("<a href=\"/RIG2=ON\"\"><button>:: เปิด ::</button></a>");
  client.println("<a href=\"/RIG2=OFF\"\"><button>::  ปิด ::</button></a><br />");

  client.println("<br><br>");
  client.print("RIG 3: ");
  client.println("<br><br>");
  client.println("<a href=\"/RIG3=ON\"\"><button>:: เปิด ::</button></a>");
  client.println("<a href=\"/RIG3=OFF\"\"><button>:: ปิด ::</button></a><br />");

  client.println("<br><br>");
  client.print("RIG 4: ");
  client.println("<br><br>");
  client.println("<a href=\"/RIG4=ON\"\"><button>:: เปิด ::</button></a>");
  client.println("<a href=\"/RIG4=OFF\"\"><button>:: ปิด ::</button></a><br />");

  client.println("</html>");
  
  delay(1);
  //Serial.println("Client disonnected");
  //Serial.println("");
  Serial.println();
  Serial.println("Status\tHumidity\tTemp");
  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t");
  Serial.print(temperature, 1);
}
