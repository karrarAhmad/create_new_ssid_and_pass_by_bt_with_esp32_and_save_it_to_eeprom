#include <EEPROM.h>
#include "BluetoothSerial.h"
//cheking the Bluetooth;
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
//create object for bluetooth
BluetoothSerial SerialBT;

//for user name
String  x;
int i;
char ssid[] = {};
//for password

String y;
int j;
char pass[] = {};


void setup() {

  Serial.begin(9600);
  // initializ the eeprom if not the esp restart
  EEPROM.begin(64);
  if (!EEPROM.begin(64)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }
  // start BT with ESP32test name
  SerialBT.begin("ESP32test");
  while (!SerialBT.available()) {
    if (SerialBT.available()) {
      x = SerialBT.readString();

      EEPROM.writeString(0, x);
      break;
    }

  }
  // separate the reading for the feils one for user name and the other for passowrd
  while (!SerialBT.available()) {
    if (SerialBT.available()) {
      y = SerialBT.readString();


      EEPROM.writeString(50, y);
      EEPROM.commit();
      break;
    }

  }

  x = EEPROM.readString(0);
  i = (x.length() + 4); //depending on the porgram or device
  ssid[i] = {};
  x.toCharArray(ssid, i);
  y = EEPROM.readString(50);
  j = (y.length() + 4); //depending on the porgram or device
  pass[j] = {};
  y.toCharArray(pass, j);
}
// here can initialize the wifi
void loop() {

  Serial.println(ssid);
  Serial.println(pass);
  delay(1000);

}
