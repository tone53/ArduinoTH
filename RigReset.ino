#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxxxxxxxxxxxxxxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "xxxxx";
char pass[] = "xxxxxx";

#define DHTPIN 14 // What DHT pin we're connected to

//Relay in Pin XX GPIOxx
#define Relay1 16
#define Relay2 5
#define Relay3 4
#define Relay4 12
//#define Relay5 0
//#define Relay6 0

// Uncomment whatever type you're using!
#define DHTTYPE DHT11     // DHT 11
//#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

// in Blynk app writes values to the Virtual Pin 1-4 (V5-V6 for DHT)
BLYNK_WRITE(V1)
{
  int RelayStatus1 = param.asInt();
  if (RelayStatus1 == 1) {
    digitalWrite(Relay1, LOW);
  }
  else {
    digitalWrite(Relay1, HIGH);
  }
}

BLYNK_WRITE(V2)
{
  int RelayStatus2 = param.asInt();
  if (RelayStatus2 == 1) {
    digitalWrite(Relay2, LOW);
  }
  else {
    digitalWrite(Relay2, HIGH);
  }
}

BLYNK_WRITE(V3)
{
  int RelayStatus3 = param.asInt();
  if (RelayStatus3 == 1) {
    digitalWrite(Relay3, LOW);
  }
  else {
    digitalWrite(Relay3, HIGH);
  }
}


BLYNK_WRITE(V4)
{
  int RelayStatus4 = param.asInt();
  if (RelayStatus4 == 1) {
    digitalWrite(Relay4, LOW);
  }
  else {
    digitalWrite(Relay4, HIGH);
  }
}
/*
BLYNK_WRITE(V7)
{
  int RelayStatus5 = param.asInt();
  if (RelayStatus5 == 1) {
    digitalWrite(Relay5, LOW);
  }
  else {
    digitalWrite(Relay5, HIGH);
  }
}

BLYNK_WRITE(V8)
{
  int RelayStatus6 = param.asInt();
  if (RelayStatus6 == 1) {
    digitalWrite(Relay6, LOW);
  }
  else {
    digitalWrite(Relay6, HIGH);
  }
}
*/

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void setup()
{
  pinMode(Relay1, OUTPUT); // sets the digital pin as output
  digitalWrite(Relay1, HIGH); // Prevents relays from starting up engaged

  pinMode(Relay2, OUTPUT); // sets the digital pin as output
  digitalWrite(Relay2, HIGH); // Prevents relays from starting up engaged

  pinMode(Relay3, OUTPUT); // sets the digital pin as output
  digitalWrite(Relay3, HIGH); // Prevents relays from starting up engaged

  pinMode(Relay4, OUTPUT); // sets the digital pin as output
  digitalWrite(Relay4, HIGH); // Prevents relays from starting up engaged
/*
  pinMode(Relay5, OUTPUT); // sets the digital pin as output
  digitalWrite(Relay5, HIGH); // Prevents relays from starting up engaged

  pinMode(Relay6, OUTPUT); // sets the digital pin as output
  digitalWrite(Relay6, HIGH); // Prevents relays from starting up engaged
*/
  // Debug console
  Serial.begin(9600);
  delay(10);

  Blynk.begin(auth, ssid, pass);


  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
