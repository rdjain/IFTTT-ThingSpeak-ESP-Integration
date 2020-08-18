
#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#define OUT_PIN 4
String myCounterReadAPIKey  = "";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "";     // replace with your wifi ssid and wpa2 key
const char *pass =  "";
const char* server = "api.thingspeak.com";

WiFiClient client;

unsigned long counterChannelNumber = ; //Enter your channel number here
const int FieldNumber1 = 1;

int set_high_key = 5; // when the field value is this the OUT_PIN is high
int set low key = 1;  // when the field value is this the OUT_PIN is low

void setup() 
{
  pinMode(OUT_PIN,OUTPUT);
  digitalWrite(OUT_PIN, LOW);
  Serial.begin(115200);
       delay(10);
       Serial.println("Connecting to ");
       Serial.println(ssid); 
 
      WiFi.mode(WIFI_STA);
      ThingSpeak.begin(client);
}
 int t = 0;
 long temp = 1;
void loop() 
{
    if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println(" ....");
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      delay(5000);
    }
    Serial.println("Connected to Wi-Fi Succesfully.");
  }

  temp = ThingSpeak.readLongField(counterChannelNumber, FieldNumber1);
  int statusCode = ThingSpeak.getLastReadStatus();
  if (statusCode == 200)
  {
    if(temp == set_high_key){
      digitalWrite(OUT_PIN,HIGH);
    }
    else if (temp == set low key){
      digitalWrite(OUT_PIN,LOW);
    }
  }
  else
  {
    Serial.println("Unable to read channel / No internet connection");
  }
  delay(100);
}
