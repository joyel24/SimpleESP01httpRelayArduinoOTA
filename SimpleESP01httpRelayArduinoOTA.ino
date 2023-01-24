/*
@File         :   SimpleESP01httpRelayArduinoOTA.ino
@Time         :   2023/01/23
@Author       :   joyel24
@Contributors :   joyel24
*/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ESP8266WebServer.h>
#include <ArduinoOTA.h>

#include "secrets.h"  //Add Your WLAN Credentials in this file


#define RELAY1          0             //Enter your relay1 pin
#define RELAY2          2             //Enter your relay2 pin
#define ON              LOW           //Define active low or active high for relays
#define OFF             HIGH          //Define active low or active high for relays
#define NumberOfRelays  2             //Define the number of relays (1 or 2)


void setup() {
  digitalWrite(RELAY1, OFF);          //Set default state to OFF
  if (NumberOfRelays > 1){
    digitalWrite(RELAY2, OFF);
  }
  pinMode(RELAY1, OUTPUT);            //Set pin as output
  if (NumberOfRelays > 1){
    pinMode(RELAY2, OUTPUT);      
  }
  
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Retry...");
    delay(1000);
    WiFi.begin(ssid, password);
    //ESP.restart();
  }
  #include "OTA.h"
}


void loop() {
  ArduinoOTA.handle();
  /*
  digitalWrite(RELAY1, ON);   //Some tests before http request handling
  digitalWrite(RELAY2, OFF);
  delay(5000);
  digitalWrite(RELAY1, OFF);
  digitalWrite(RELAY2, ON);
  delay(5000);                //tests
  */
}
