#include <Arduino.h>
#include <WiFi.h>

/*
const string WIFI_NETWORK = "BS_AP_Z_5_3"; //my ssid
const string WIFI_PASSWORD = "kalosavvatokiriako2023"; //password
*/
String WIFI_NETWORK = "Dragonphoenix Inn"; //my ssid
String WIFI_PASSWORD = "Elminister"; //password


void ConnectToWiFi(String WIFI_NETWORK, String WIFI_PASSWORD);

IPAddress staticIP(192, 168, 100, 45);
IPAddress gateway(192, 168, 100, 1);         
IPAddress subnet(255, 255, 255, 0);

int status = WL_IDLE_STATUS;


void setup() {
  Serial.begin(115200);
  ConnectToWiFi(WIFI_NETWORK, WIFI_PASSWORD);
}

void loop() {
  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
}

void ConnectToWiFi(String WIFI_NETWORK, String WIFI_PASSWORD) {
  Serial.print("Connecting to WiFi");

  WiFi.mode(WIFI_STA);

  Serial.println("\nTrying to get an IP address using DHCP");
  WiFi.begin(WIFI_NETWORK.c_str(), WIFI_PASSWORD.c_str());
  
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() != WL_CONNECTED){
    Serial.println("DHCP failed. Initialize with static IP");
    WiFi.config(staticIP, gateway, subnet);

    while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
    }

     if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Connection failed!");
     }
  }
  else{
    Serial.print("\nConected to WiFi network with local IP address:");
    Serial.println(WiFi.localIP()); 
  }
}