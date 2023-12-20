/*
BON STUDIO
"BS_AP_Z_5_3"
"kalosavvatokiriako2023"

PEDRO
"MyrDyn"
"M90b53M98pj62@"

ARTINA
"ARTINA WIFI"
""

DRAGONPHOENIX
"Dragonphoenix Inn"
"Elminister"
*/
#include <Arduino.h>

void BluetoothInitialize();
void WifiCredentialsViaSerial(char WiFi_network[], char WiFi_password[]);
void ConnectToWiFi_BT(const char *WIFI_NETWORK, const char *WIFI_PASSWORD);

int status = WL_IDLE_STATUS;
char WiFi_ssid[32];
char WiFi_pswd[32];

/*
//checking if BT is properly enabled
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif
*/
BluetoothSerial SerialBT;

void setup()
{
  Serial.begin(115200);
  SerialBT.begin("YannosESP32");
}

void loop()
{
  while (WiFi.status() == WL_CONNECTED)
  {
    Serial.print("\nWiFi_network: ");
    Serial.println(WiFi_ssid);
    Serial.print("\nWiFi_password: ");
    Serial.println(WiFi_pswd);
    delay(1000);
  }

  while (WiFi.status() != WL_CONNECTED)
  {
    BluetoothInitialize();

    WifiCredentialsViaSerial(WiFi_ssid, WiFi_pswd);

    ConnectToWiFi_BT(WiFi_ssid, WiFi_pswd);
  }
}

void BluetoothInitialize()
{
  Serial.println("Wait until someone sends something via Bluetooth");
  while (!SerialBT.available())
  {
  }
  Serial.println("BT initialised");
  // initialisation
  SerialBT.println("Dumping BT data:");
  char dump[32];
  if (SerialBT.available())
  {
    SerialBT.readBytes(dump, sizeof(dump));
    SerialBT.println(dump);
  }
}

void WifiCredentialsViaSerial(char WiFi_network[], char WiFi_password[])
{
  SerialBT.print("\nAdd WiFi SSID: ");
  while (!Serial.available())
  {
    delay(1);
  }
  SerialBT.readBytes(WiFi_network, 32);
  WiFi_network[31] = '\0';
  String ssidString = WiFi_network;
  ssidString.trim();
  ssidString.toCharArray(WiFi_network, 32);
  Serial.print("\nWiFi_network: ");
  Serial.println(WiFi_network);

  SerialBT.print("\nAdd WiFi password: ");
  while (!Serial.available())
  {
    delay(1);
  }
  SerialBT.readBytes(WiFi_password, 32);
  WiFi_password[31] = '\0';
  String pswdString = WiFi_password;
  pswdString.trim();
  pswdString.toCharArray(WiFi_password, 32);
  Serial.print("\nWiFi_password: ");
  Serial.println(WiFi_password);
}

void ConnectToWiFi_BT(const char *WIFI_NETWORK, const char *WIFI_PASSWORD)
// It's a good practice to use const when the function does not intend to modify the string data
{
  SerialBT.print("Connecting to WiFi");

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    SerialBT.print(".");
    delay(500);
  }

  if (WiFi.status() != WL_CONNECTED)
  {
    SerialBT.println("Connection failed!");
  }
  else
  {
    SerialBT.print("\nConected to WiFi network with local IP address:");
    SerialBT.println(WiFi.localIP());
  }
}