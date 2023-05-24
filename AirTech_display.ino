#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <SDS011.h>
#include <DHT.h>
#include <Adafruit_CCS811.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1 // Reset pin not used for SSD1306
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN D1         // Pin to which the DHT11 sensor is connected
#define DHTTYPE DHT11     // DHT sensor type (DHT11 or DHT22)

DHT dht(DHTPIN, DHTTYPE);

SDS011 mySensor(D2, D1); // RX, TX pins

Adafruit_CCS811 ccs; // CCS811 sensor object

#define OZONE_PIN A0 // Pin to which the ozone sensor is connected

void setup() {
  Serial.begin(115200);
  
  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("SSD1306 initialization failed");
    while (1);
  }

  // Initialize DHT11 sensor
  dht.begin();

  // Initialize SDS011 sensor
  mySensor.begin();

  // Initialize CCS811 sensor
  if (!ccs.begin()) {
    Serial.println("CCS811 sensor initialization failed");
    while (1);
  }

  // Set CCS811 measurement mode to constant power mode
  ccs.setDriveMode(CCS811_DRIVE_MODE_1SEC);

  // Initialize analog ozone sensor
  pinMode(OZONE_PIN, INPUT);
}

void loop() {
  // Read DHT11 sensor data
  delay(2000);
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Read SDS011 sensor data
  if (mySensor.read()) {
    float pm25_high_byte = mySensor.getPM2P5High();
    float pm25_low_byte = mySensor.getPM2P5Low();
    float pm10_high_byte = mySensor.getPM10High();
    float pm10_low_byte = mySensor.getPM10Low();

    float pm25 = ((pm25_high_byte * 256) + pm25_low_byte) / 10;
    float pm10 = ((pm10_high_byte * 256) + pm10_low_byte) / 10;

    // Read CCS811 sensor data
    if (ccs.available()) {
      if (!ccs.readData()) {
        float tvoc = ccs.getTVOC();
        float co2 = ccs.geteCO2();

        // Read ozone sensor data
        int ozoneSensorValue = analogRead(OZONE_PIN);
        float ozoneConcentration = calculateOzoneConcentration(ozoneSensorValue);

        // Display measurements on OLED display
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, 0);
        display.print("Temp: ");
        display.print(temperature);
        display.println("C");
        display.print("Humidity: ");
        display.print(humidity);
        display.println("%");
        display.print("PM2.5: ");
        display.print(pm25);
        display.println(" ug/m^3");
        display.print("PM10: ");
        display.print(pm10);
        display.println(" ug/m^3");
        display.print("TVOC: ");
        display.print(tvoc);
        display.println(" ppb");
        display.print("CO2: ");
        display.print(co2);
        display.println(" ppm");
        display.print("Ozone: ");
        display.print(ozoneConcentration);
        display.println(" ppb");
        display.display();
      }
    }
  }

  delay(1000); // Wait for 1 second before taking the next reading
}

float calculateOzoneConcentration(int sensorValue) {
  // Convert sensor value to voltage
  float voltage = (sensorValue / 1024.0) * 5.0;

  // Apply the calibration and conversion formula
  float concentration = (voltage - 0.15) / 0.6;

  return concentration;
}
