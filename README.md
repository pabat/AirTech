# AirTech
Air Qaulity Monitoring System

### Key Features:
**Real-time Monitoring:** The system continuously monitors the air quality and provides real-time data on various parameters such as temperature, humidity, particulate matter (PM2.5, PM10), VOCs, CO2 levels, and ozone concentration. This real-time monitoring allows for immediate detection and response to any changes or issues in the air quality.

**Wireless Connectivity:** The system incorporates wireless technologies such as Wi-Fi, enabling seamless communication between the monitoring devices and the mobile application or central server. This allows users to access the air quality data remotely and receive alerts or notifications on their smartphones or other devices.
**Mobile Application Integration:** The system integrates with a mobile application, which provides a user-friendly interface for visualizing and interacting with the air quality data. Users can access real-time measurements and historical data and set alerts through the mobile app.

**Alerts and Notifications:** The system can send automated alerts and notifications to users' mobile devices when the air quality exceeds certain thresholds or if any abnormal conditions are detected. This enables users to take immediate action or change to maintain a healthy environment.

#### Sensors' specs:

**DHT11**: The DHT11 sensor is an affordable option for measuring temperature and humidity. It allows monitoring of indoor climate conditions, which can impact comfort and health.

**SDS011**:

**ENS160**: The ENS160 sensor can measrure Carbon Dioxide (CO2) and Volatile Organic Compounds (VOCs) simultaneously.
* It incorporates intelligent algorithms that perform advanced processing of raw sensor measurements directly on the chip enabling accurate calculations of all measurings without overwhelming the main host processor.
* It is built to be maintenance-free, reducing the need for frequent calibration or replacement, which is essential for continuous and reliable operation.
* It offers both I2C and SPI digital interfaces, providing flexibility and ease of integration with various microcontrollers. 
* It is available in a compact LGA package, making it easy to mount on a printed circuit board (PCB) or integrate into existing devices. The sensor also features an SPI or I2C slave interface with a separate VDDIO and simplifies the integration process and ensures efficient data exchange between the sensor and the system.

**MQ131**: The MQ131 sensor specializes in detecting Ozone (O3). MQ131 has several features that make it a suitable choice for a smart air quality monitoring system:
* It has a high sensitivity to ozone in a wide range, which means it can detect even low ozone concentrations in the air.
* It has a long lifespan and is relatively low cost, making it an affordable option for large-scale air quality monitoring systems.
* Its simple drive circuit makes it easy to integrate into existing systems and combine with other sensors.
* It is widely used in domestic and industrial ozone concentration alarms and portable ozone concentration detectors.

**_Technical details:_**
- Sensitivity: 0.1 - 10ppm Ozone
- Response time: <10s
- Recovery time: <30s
- Heater voltage: 5.0V ±0.2V AC or DC
- Load resistance: adjustable (recommended value is about 20kΩ)
- Operating temperature range: -10°C to +50°C
- Storage temperature range: -20°C to +70°C

