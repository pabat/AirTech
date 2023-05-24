# AirTech
Air Qaulity Monitoring System

### Key Features:
**Real-time Monitoring:** The system continuously monitors the air quality and provides real-time data on various parameters such as temperature, humidity, particulate matter (PM2.5, PM10), VOCs, CO2 levels, and ozone concentration. This real-time monitoring allows for immediate detection and response to any changes or issues in the air quality.

**Wireless Connectivity:** The system incorporates wireless technologies such as Wi-Fi, enabling seamless communication between the monitoring devices and the mobile application or central server. This allows users to access the air quality data remotely and receive alerts or notifications on their smartphones or other devices.
**Mobile Application Integration:** The system integrates with a mobile application, which provides a user-friendly interface for visualizing and interacting with the air quality data. Users can access real-time measurements and historical data and set alerts through the mobile app.

**Alerts and Notifications:** The system can send automated alerts and notifications to users' mobile devices when the air quality exceeds certain thresholds or if any abnormal conditions are detected. This enables users to take immediate action or change to maintain a healthy environment.

## Sensors' specs:

**DHT11**: The DHT11 sensor is an affordable option for measuring temperature and humidity. 
* It has calibrated digital signal output for accurate temperature and humidity measurement. 
* It has resistant-type humidity and NTC temperature measurements for reliable sensing. 
* It has a single-wire serial interface for easy system integration.
* It has a small size, low power consumption, and up to 20-meter signal transmission range make.

**SDS011**: The SDS011 sensor can measure particulate matter (PM2.5 and PM10) in the air, providing information about air pollution levels.
`PM2.5 value: PM2.5 (μg/m³) = ((PM2.5 High byte * 256) + PM2.5 low byte) / 10`
`PM10 value: PM10 (μg/m³) = ((PM10 high byte * 256) + PM10 low byte) / 10`

* It uses the laser scattering principle to detect particles in the air. When particles pass through the detecting area, light scattering is induced, which is then transformed into electrical signals. 
* It can detect particle concentrations between 0.3 to 10μm in less than 10 seconds. 
* It has a high resolution of 0.3μg/m3 for precise measurements of PM2.5 & PM10 particles.
* It can easily be integrated with its UART output and built-in fan. UART output allows for communication with other devices, while its built-in fan ensures stable and consistent readings over time by preventing dust accumulation on the sensor's surface.

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
