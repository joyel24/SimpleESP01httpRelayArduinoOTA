/*
@File         :   SimpleESP01httpRelayArduinoOTA.ino
@Time         :   2023/01/23
@Author       :   joyel24
@Contributors :   joyel24
*/

#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "JoSa"                //Enter your own SSID
#define STAPSK "bienvenue"            //Enter your WiFi password
#endif

#define RELAY1          0             //Enter your relay1 pin
#define RELAY2          2             //Enter your relay2 pin
#define ON              LOW           //Define active low or active high for relays
#define OFF             HIGH          //Define active low or active high for relays
#define NumberOfRelays  2             //Define the number of relays (1 or 2)

const char* ssid = STASSID;
const char* password = STAPSK;




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
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {  // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ArduinoOTA.handle();
  
  digitalWrite(RELAY1, ON);   //Some tests before http request handling
  digitalWrite(RELAY2, OFF);
  delay(5000);
  digitalWrite(RELAY1, OFF);
  digitalWrite(RELAY2, ON);
  delay(5000);                //tests
}
