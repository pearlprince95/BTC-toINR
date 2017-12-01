/*******************************************************************
 *  An example of currency conversion and displaying it over OLED  *
 *  using currencylayerapi                                                        *
 *                                                                 *
 *  written by MUTHUKUMAR P (pearlprince95 on Github)              *
 *  adapted by Brian Lough                                         *
 *******************************************************************/
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <String.h>
#include <Wire.h>
#include "SSD1306.h"
#include <ESP8266mDNS.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
char ssid[] = "pearlprince95";     // your network SSID (name)
char password[] = "MAHARANI"; // your network key
SSD1306 display(0x3c, D1, D2);
unsigned long previousMillis = 0;
const long interval = 40000;
void setup() 
{
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(600);
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  pinMode(LED_BUILTIN, OUTPUT); // initialize digital ledPin as an output.
  delay(10);
  digitalWrite(LED_BUILTIN, LOW); // initialize pin as off
  display.init();
  display.flipScreenVertically(); 

      display.clear();
     display.setFont(ArialMT_Plain_16);
     display.drawStringMaxWidth(0,0,120,"Loading.. " );
     display.display();
}

void loop() 
{

 unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
  
  
 HTTPClient http;  //Declare an object of class HTTPClient
 Serial.println("payload");
   // http.begin("http://apilayer.net/api/live?access_key=58cdbc49e16a52138264305fc87dd265&currencies=INR&source=USD"); 
     http.begin("http://api.coindesk.com/v1/bpi/currentprice/inr");
    Serial.println("payload_1");
    int httpCode = http.GET();                                                      
    if (httpCode > 0) 
    { 
     String payload = http.getString(); 
     const size_t bufferSize = JSON_OBJECT_SIZE(2) + 2*JSON_OBJECT_SIZE(3) + 2*JSON_OBJECT_SIZE(4) + 500;
DynamicJsonBuffer jsonBuffer(bufferSize);
     JsonObject& root = jsonBuffer.parseObject(payload); 
     JsonObject& bpi_INR = root["bpi"]["INR"];
     const char* bpi_INR_rate = bpi_INR["rate"];
     String Bpi_INR_rate = String(bpi_INR_rate);
     Serial.println(Bpi_INR_rate);
     Serial.println("inr");
     Serial.println(payload.substring(434, 447));
     display.clear();
     display.setFont(ArialMT_Plain_16);
     display.drawStringMaxWidth(0,0,120,"BTC to INR " + Bpi_INR_rate );
     display.display();
    }
    http.end(); 
    }
       
}


