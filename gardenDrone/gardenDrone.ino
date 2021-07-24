#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <Wire.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <WiFiUdp.h>

//PINS
const int RED_DATA_PIN = 0;
const int WIFI_INFO_LED_PIN = 2;
const int PUMP_ACTIVATE_PIN = 12;
#define echoPin 13
const int WIFI_RESET_PIN = 14;
#define trigPin 15

//vars
const int  statusPagePort = 8266;
const char* SOFTWARE_VERSION = "1.0 Garden Drone";
const char* DEVICENAME = "GardenDroneMain"; 
const long ACTIVATE_DURATION = 300000;
const long CHECK_WIFI_INTERVAL = 30000;
long duration;
int distance;
int distanceIn;
unsigned long deviceActivateStart;
unsigned long currMillis = millis();

MDNSResponder mdns;
ESP8266WebServer server(statusPagePort); //this cant be running on port 80 because of the wifimanager
WiFiClient espClient;
WiFiManager wifiManager;

void setup() {
  Serial.begin(9600);
  pinMode(PUMP_ACTIVATE_PIN,OUTPUT);
  digitalWrite(PUMP_ACTIVATE_PIN,HIGH);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //wifiManager.setSTAStaticIPConfig(IPAddress(6,13,0,218), IPAddress(6,13,0,1), IPAddress(255,255,255,0)); //Remove this for DHCP
  wifiManager.setHostname(DEVICENAME);
  if(!wifiManager.autoConnect("ESPSetup", "wifiSetup1")){
    wifiManager.autoConnect("ESPSetup", "wifiSetup1");
  }
  setupWeb();
}

//main loop
void loop() {
  // wire a button with a 10k resistor to ground and the other end to pin 14 for resetting and to prompt for new network
  if ( digitalRead(WIFI_RESET_PIN) == LOW ) {
    WiFiManager wifiManager;
    wifiManager.setTimeout(600);
    WiFi.mode(WIFI_STA);
    wifiManager.startConfigPortal("OnDemandAP");
    Serial.println("Autoconnect portal running");
  }

  server.handleClient();
}
