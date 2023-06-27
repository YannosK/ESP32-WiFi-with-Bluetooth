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

void ConnectToWiFi_BT(const char* WIFI_NETWORK, const char* WIFI_PASSWORD);

int status = WL_IDLE_STATUS;

/*
//checking if BT is properly enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
*/

BluetoothSerial SerialBT; //instance of BluetoothSerial


void setup() {
  Serial.begin(115200);
  SerialBT.begin("YannosESP32"); //device name

  Serial.println("Wait until someone sends something via Bluetooth");

  while(!SerialBT.available()){}
  Serial.println("BT initialised");

  //initialisation
  SerialBT.println("Dumping BT data:");
  char dump[32];
  if (SerialBT.available()) {
    SerialBT.readBytes(dump, sizeof(dump));
    SerialBT.println(dump);
  }

  char WiFi_ssid[32];
  char WiFi_pswd[32];

  SerialBT.print("\nAdd WiFi SSID: ");
  while(!SerialBT.available()){
    delay(1);
  }
  SerialBT.readBytes(WiFi_ssid, sizeof(WiFi_ssid));
  /*
  WiFi_ssid[sizeof(WiFi_ssid) - 1] = '\0';
  WiFi_ssid[strcspn(WiFi_ssid, "\r")] = '\0';
  */
  // alternate way to trim char[] is to make it String
  String ssidString = WiFi_ssid;
  ssidString.trim();
  ssidString.toCharArray(WiFi_ssid, sizeof(WiFi_ssid));  
  Serial.print("\nWiFi_ssid: ");
  Serial.println(WiFi_ssid);

  SerialBT.print("\nAdd WiFi password: ");
  while(!SerialBT.available()){
    delay(1);
  }
  SerialBT.readBytes(WiFi_pswd, sizeof(WiFi_pswd));
  /*
  WiFi_pswd[sizeof(WiFi_pswd) - 1] = '\0';
  WiFi_pswd[strcspn(WiFi_pswd, "\r")] = '\0';
  */
  // alternate way to trim char[] is to make it String
  String pswdString = WiFi_pswd;
  pswdString.trim();
  pswdString.toCharArray(WiFi_pswd, sizeof(WiFi_pswd));  
  Serial.print("\nWiFi_pswd: ");
  Serial.println(WiFi_pswd);

  ConnectToWiFi_BT(WiFi_ssid, WiFi_pswd);
}

void loop() {
  Serial.print("\nIP address: ");
  Serial.println(WiFi.localIP());
  SerialBT.print("\nIP address: ");
  SerialBT.println(WiFi.localIP());
  delay(1000);
}


 //It's a good practice to use const when the function does not intend to modify the string data
void ConnectToWiFi_BT(const char* WIFI_NETWORK, const char* WIFI_PASSWORD) {
  SerialBT.print("Connecting to WiFi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED){
    SerialBT.print(".");
    delay(500);
  }

  if (WiFi.status() != WL_CONNECTED){
    SerialBT.println("Connection failed!");
  }
  else{
    SerialBT.print("\nConected to WiFi network with local IP address:");
    SerialBT.println(WiFi.localIP()); 
  }
}