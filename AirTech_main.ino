#include <SDS011.h>
#include <FirebaseESP32.h>
#include <WiFi.h>
#include <DHT.h>
#include <Wire.h>

#define WIFI_SSID "YourWiFiSSID"
#define WIFI_PASSWORD "YourWiFiPassword"

#define FIREBASE_HOST "https://air-monitoring-system-7bb90-default-rtdb.europe-west1.firebasedatabase.app/measurements/50003001"
#define FIREBASE_AUTH "#####

#define SENSOR_DATA_PATH "/sensor_data"

FirebaseData firebaseData;

SDS011 mySensor(D2, D1); // SDS011 RX, TX pins
DHT dht(DHTPIN, DHTTYPE); // DHT11 sensor

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }

  // Initialize Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  // Initialize SDS011 sensor
  mySensor.begin();

  // Initialize DHT11 sensor
  dht.begin();

  // Initialize I2C bus
  Wire.begin();
}

void loop() {
  // Read SDS011 sensor data
  if (mySensor.read()) {
    float pm25_high_byte = mySensor.getPM2P5High();
    float pm25_low_byte = mySensor.getPM2P5Low();
    float pm10_high_byte = mySensor.getPM10High();
    float pm10_low_byte = mySensor.getPM10Low();

    float pm25 = ((pm25_high_byte * 256) + pm25_low_byte) / 10;
    float pm10 = ((pm10_high_byte * 256) + pm10_low_byte) / 10;

    Serial.print("PM2.5: ");
    Serial.print(pm25);
    Serial.print(" µg/m³\tPM10: ");
    Serial.print(pm10);
    Serial.println(" µg/m³");

    // Update Firebase with SDS011 sensor data
    Firebase.setFloat(firebaseData, SENSOR_DATA_PATH + "/PM2.5", pm25);
    Firebase.setFloat(firebaseData, SENSOR_DATA_PATH + "/PM10", pm10);
    if (Firebase.failed()) {
      Serial.println("Error updating SDS011 sensor data to Firebase");
      Serial.println(firebaseData.errorReason());
    } else {
      Serial.println("SDS011 sensor data updated to Firebase");
    }
  }

  // Read DHT11 sensor data
  delay(2000);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read data from DHT11 sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Update Firebase with DHT11 sensor data
    Firebase.setFloat(firebaseData, SENSOR_DATA_PATH + "/Temperature", temperature);
    Firebase.setFloat(firebaseData, SENSOR_DATA_PATH + "/Humidity", humidity);
    if (Firebase.failed()) {
      Serial.println("Error updating DHT11 sensor data to Firebase");
      Serial.println(firebaseData.errorReason());
    } else {
      Serial.println("DHT11 sensor data updated to Firebase");
    }
  }

  // Read ENS160 sensor data
  delay(2000);
  byte tvoc_MSB = Wire.readReg(sensor_address, 0x22);
  byte tvoc_LSB = Wire.readReg(sensor_address, 0x23);
  byte eco2_MSB = Wire.readReg(sensor_address, 0x24);
  byte eco2_LSB = Wire.readReg(sensor_address, 0x25);

  int tvoc = (tvoc_MSB * 256) + tvoc_LSB;
  int eco2 = (eco2_MSB * 256) + eco2_LSB;

  Serial.print("VOC: ");
  Serial.print(tvoc);
  Serial.println(" ppb");
  Serial.print("CO2: ");
  Serial.print(eco2);
  Serial.println(" ppm");

  // Calculate ozone concentration
  float ozoneConcentration = calculateOzoneConcentration(sensorValue);

  // Update Firebase with ENS160 sensor data
  Firebase.setInt(firebaseData, SENSOR_DATA_PATH + "/TVOC", tvoc);
  Firebase.setInt(firebaseData, SENSOR_DATA_PATH + "/CO2", eco2);
  Firebase.setFloat(firebaseData, SENSOR_DATA_PATH + "/OzoneConcentration", ozoneConcentration);
  if (Firebase.failed()) {
    Serial.println("Error updating ENS160 sensor data to Firebase");
    Serial.println(firebaseData.errorReason());
  } else {
    Serial.println("ENS160 sensor data updated to Firebase");
  }

  delay(5000);
}

float calculateOzoneConcentration(int sensorValue) {
  // Convert sensor value to voltage
  float voltage = (sensorValue / 1024.0) * 5.0;

  // Apply the calibration and conversion formula
  float concentration = (voltage - 0.15) / 0.6;

  return concentration;
}
