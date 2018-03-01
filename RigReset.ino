#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "xxxxxxxxxxxxxxxx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "WIFI";
char pass[] = "Wifipass";

//Relay in Pin XX - GPIOxx
#define Relay1 16
#define Relay2 5
#define Relay3 4
#define Relay4 12
//#define Relay5 6
//#define Relay6 5

// in Blynk app writes values to the Virtual Pin V1- V4 (V5-6 for temp)
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

  // communication with the host computer
  Serial.begin(9600);
  delay(10);

  Blynk.begin(auth, ssid, pass);

}

void loop()
{
  Blynk.run();
}
