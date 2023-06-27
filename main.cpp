#include <Arduino.h>
#include <WiFi.h>
#include <BluetoothSerial.h>

/*
const string WIFI_NETWORK = "BS_AP_Z_5_3"; //my ssid
const string WIFI_PASSWORD = "kalosavvatokiriako2023"; //password

String WIFI_NETWORK = "Dragonphoenix Inn"; //my ssid
String WIFI_PASSWORD = "Elminister"; //password

String WIFI_NETWORK = "ARTINA WIFI "; //my ssid
String WIFI_PASSWORD = ""; //password
*/

void ConnectToWiFi_BT(String WIFI_NETWORK, String WIFI_PASSWORD);

IPAddress staticIP(192, 168, 100, 45);
IPAddress gateway(192, 168, 100, 1);         
IPAddress subnet(255, 255, 255, 0);

int status = WL_IDLE_STATUS;

//checking if BT is properly enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT; //instance of BluetoothSerial


void setup() {
  Serial.begin(115200);
  SerialBT.begin("YannosESP32"); //device name

  //initialisation
  SerialBT.println("You are connected to ESP32.\nPlease send nothing and wait for a moment.");
  int i=0;
  String dump;
  while(i<5) {
    SerialBT.print(".");
    delay(1000);
    dump = SerialBT.readString();
    i++;
  }
  SerialBT.print("\n");
  //getting rid of the first messages both in the serial and Bluetooth monitor
  if(SerialBT.available()){
    Serial.print("Dumping BT data:");
    Serial.println(dump);
    SerialBT.print("Dumping data:");
    SerialBT.println(dump);
  }

  String WiFi_ssid;
  String WiFi_pswd;

  SerialBT.print("\nAdd WiFi SSID: ");
  while(!SerialBT.available()){
    delay(1);
  }
  WiFi_ssid = SerialBT.readString();
  WiFi_ssid.trim();
  Serial.println(WiFi_ssid.c_str());

  SerialBT.print("\nAdd WiFi password: ");
  while(!SerialBT.available()){
    delay(1);
  }
  WiFi_pswd = SerialBT.readString();
  WiFi_pswd.trim();
  Serial.println(WiFi_pswd.c_str()); 

  ConnectToWiFi_BT(WiFi_ssid, WiFi_pswd);
}

void loop() {
  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
  SerialBT.print("\nIP address: ");
  SerialBT.println(WiFi.localIP());
  delay(1000);
}

void ConnectToWiFi_BT(String WIFI_NETWORK, String WIFI_PASSWORD) {
  SerialBT.println("Connecting to WiFi");

  WiFi.mode(WIFI_STA);

  SerialBT.println("\nTrying to get an IP address using DHCP");
  WiFi.begin(WIFI_NETWORK.c_str(), WIFI_PASSWORD.c_str());
  
  while (WiFi.status() != WL_CONNECTED){
    SerialBT.print(".");
    delay(500);
  }

  if (WiFi.status() != WL_CONNECTED){
    SerialBT.println("DHCP failed. Initialize with static IP");
    WiFi.config(staticIP, gateway, subnet);

    while (WiFi.status() != WL_CONNECTED){
    SerialBT.print(".");
    delay(500);
    }

     if (WiFi.status() != WL_CONNECTED) {
      SerialBT.println("Connection failed!");
     }
  }
  else{
    SerialBT.print("\nConected to WiFi network with local IP address:");
    SerialBT.println(WiFi.localIP()); 
  }
}