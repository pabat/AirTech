#include <ESP8266WiFi.h>
#include <WiFiUDP.h>
#include <ArduinoJson.h>
#include <NTPClient.h>
#include <EEPROM.h>
#include <common.h>
#include <FirebaseESP8266.h>
#include <FirebaseFS.h>
#include <Utils.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <Wire.h>

#include "ScioSense_ENS160.h"
ScioSense_ENS160 ens160(ENS160_I2CADDR_0);

#include "DHT.h"
#define DHTPIN D8
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

#include <Arduino.h>
#include <SdsDustSensor.h>
const int SDS_RX_PIN = TX;
const int SDS_TX_PIN = RX; 
SoftwareSerial softwareSerial(SDS_RX_PIN, SDS_TX_PIN);
SdsDustSensor sds(softwareSerial);
const int MINUTE = 60000;
const int WAKEUP_WORKING_TIME = 30000;
const int MEASUREMENT_INTERVAL = 5 * MINUTE;

#include "MQ131.h"

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

#define FIREBASE_HOST "hostname"
#define FIREBASE_AUTH "auth"

String get_login() {
  String login = "";
  char c;
  for (int addr = 0; addr < 32; addr++) {
    c = char(EEPROM.read(addr));
    if (c == '\n')
      break;
    login.concat(c);
  }
  return login;
}

String get_pass() {
  String pass = "";
  char c;
  for (int addr = 32; addr < 64; addr++) {
    c = char(EEPROM.read(addr));
    if (c == '\n')
      break;
    pass.concat(c);
  }
  return pass;
}

String set_login() {
  String login = "";
  int addr = 0;
  char c;
  while (Serial.available()) {
    c = Serial.read();
    Serial.println(c);
    delay(200);
    if (c == '|')
      break;
    EEPROM.write(addr, c);
    addr++;
    login.concat(c);
  }
  addr++;
  EEPROM.write(addr, '\n');
  return login;
}

String set_pass() {
  String pass = "";
  int addr = 32;
  char c;
  while (Serial.available()) {
    c = Serial.read();
    Serial.println(c);
    delay(200);
    if (c == '|')
      break;
    EEPROM.write(addr, c);
    addr++;
    pass.concat(c);
  }
  addr++;
  EEPROM.write(addr, '\n');
  return pass;
}

void flush_memory() {
  EEPROM.begin(64);
  for (int addr = 0; addr < 64; addr++) {
    EEPROM.write(addr, '\n');
  }
  EEPROM.commit();
}

String login;
String pass;

String db_PM25_value = "";
String db_PM10_value = "";
String db_CO2_value = "";
String db_VOC_value = "";
String db_AQI_value = "";
String db_O3_value = "";
String db_Temperature_value = "";
String db_Humidity_value = "";

void setup() {
  EEPROM.begin(64);
  Serial.begin(115200);
  login = get_login();
  pass = get_pass();

  if (login == "" || pass == "") {
    while (!Serial.available())
      delay(500);
    login = set_login();
    pass = set_pass();
    WiFi.begin(login, pass);
    while (WiFi.status() != WL_CONNECTED) {}
  }
  else {
    WiFi.begin(login, pass);
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 10) {
      attempts++;
    }
    if (WiFi.status() != WL_CONNECTED) {
      flush_memory();
      while (!Serial.available()) {}
      login = set_login();
      pass = set_pass();
      WiFi.begin(login, pass);
      while (WiFi.status() != WL_CONNECTED) {
      }
    }
  }
  EEPROM.commit();
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
  while (!Serial) {}
  ens160.begin();
  if (ens160.available()) {
    ens160.setMode(ENS160_OPMODE_STD)
  }
  dht.begin();
  sds.begin();
}

void data_to_Firebase(String date = ""){
  String entry = "{\"date\":" + date + ", \"measurements\":{\"AQI\"" + db_AQI_value+ "\"PM25\"" + db_PM25_value+", \"PM10\"" + db_PM10_value+",\"CO2\"" + db_CO2_value+",\"VOC\"" + db_VOC_value  +",\"O3\"" + db_O3_value+",\"Temperature\"" + db_Temperature_value+",\"Humidity\"" + db_Humidity_value+"}}";
  Firebase.pushString("/", entry);
}

void loop() {
  //CO2, TVOC, AQI measurements
  float AQI = 0.0;
  float TVOC = 0.0;
  float CO2 = 0.0;
  float hum = 0.0;
  float temp = 0.0;
  float pm25 = 0.0;
  float pm10 = 0.0;
  float O3 = 0.0;
  if (ens160.available()) {
    ens160.measure(0);
    AQI = ens160.getAQI();
    TVOC = ens160.getTVOC();
    CO2 = ens160.geteCO2();
  }
  //temperature and humidity measurements
  hum = dht.readHumidity();
  temp = dht.readTemperature();
  //O3 measurements
  O3 = analogRead(A0);
  //PM2.5 and PM10 measurements
  sds.wakeup();
  delay(WAKEUP_WORKING_TIME);
  PmResult pm = sds.queryPm();
  if (pm.isOk()) {
    pm25 = pm.pm25;
    pm10 = pm.pm10;
  }
  WorkingStateResult state = sds.sleep();
  db_PM25_value = String(pm25);
  db_PM10_value = String(pm10);
  db_CO2_value = String(CO2);
  db_VOC_value = String(TVOC);
  db_AQI_value = String(AQI);
  db_O3_value = String(O3);
  db_Temperature_value = String(temp);
  db_Humidity_value = String(hum);
  data_to_Firebase();
  delay(MEASUREMENT_INTERVAL);
}
