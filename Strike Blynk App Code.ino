#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "W7W_rnAUXVIKc1cGdCetmTo02D4MnRtq";       // You should get Auth Token in the Blynk App.
const int BUTTON = 0;                 // switch 1 of BlynkBoard Conneted with D9(GPIO 03) pin of NodeMCU
char ssid[] = "AirPennNet-Device";    // Your WiFi credentials.
char pass[] = "penn1740wifi";             // Set password to "" for open networks.
int BUTTONstate;

void setup()
  {
  Serial.begin(9600);                 // Debug console
  Blynk.begin(auth, ssid, pass);
  pinMode (BUTTON, INPUT);
  }

void loop()
  {
  Blynk.run();
  BUTTONstate = digitalRead(BUTTON);
  Serial.println(BUTTONstate);
  }
  
