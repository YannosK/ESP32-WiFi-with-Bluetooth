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

  //initialisation
  SerialBT.println("You are connected to ESP32.\nPlease send nothing and wait for a moment.");
  int i=0;
  int dump;
  while(i<5) {
    delay(1000);
    dump = SerialBT.read();
    i++;
  }

  //getting rid of the first messages both in the serial and Bluetooth monitor
  if(SerialBT.available()){
    Serial.print("Dumping BT data:");
    Serial.println(dump);
    SerialBT.print("Dumping data:");
    SerialBT.println(dump);
  }

  char WiFi_ssid[32];
  char WiFi_pswd[32];

  SerialBT.print("\nAdd WiFi SSID: ");
  while(!SerialBT.available()){
    delay(1);
  }
  SerialBT.readBytes(WiFi_ssid, sizeof(WiFi_ssid));
  WiFi_ssid[sizeof(WiFi_ssid) - 1] = '\0';
  //Serial.println(WiFi_ssid);

  SerialBT.print("\nAdd WiFi password: ");
  while(!SerialBT.available()){
    delay(1);
  }
  SerialBT.readBytes(WiFi_pswd, sizeof(WiFi_pswd));
  WiFi_pswd[sizeof(WiFi_pswd) - 1] = '\0';
  //Serial.println(WiFi_ssid);

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
  SerialBT.println("Connecting to WiFi");

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