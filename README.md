🚀 MQ-8 Hydrogen Gas Sensor with ESP32, LCD, and MQTT

This project reads hydrogen concentration levels from an MQ-8 Gas Sensor, displays the values on an I2C LCD, and publishes them to an MQTT broker for remote monitoring.

📌 Features

Connects ESP32 to Wi-Fi.

Reads analog data from MQ-8 sensor.

Displays hydrogen levels on a 16x2 I2C LCD.

Publishes sensor data to MQTT broker (broker.mqtt-dashboard.com by default).

Compatible with MQTT dashboards (e.g., MQTT Explorer, Node-RED, Home Assistant).

🛠️ Hardware Required

ESP32 development board

MQ-8 Hydrogen Gas Sensor (analog output used)

16x2 LCD with I2C module

Breadboard and jumper wires

5V power supply

⚡ Circuit Connections
MQ-8 Sensor Pin	ESP32 Pin
VCC	5V
GND	GND
AOUT	GPIO34 (ADC)
LCD Pin	ESP32 Pin
SDA	GPIO21
SCL	GPIO22
VCC	5V
GND	GND
📦 Software Dependencies

Install the following libraries in Arduino IDE / PlatformIO:

LiquidCrystal_I2C

PubSubClient

WiFi (comes with ESP32 core)

💻 Setup Instructions

Clone this repository:

git clone https://github.com/yourusername/mq8-mqtt-esp32.git
cd mq8-mqtt-esp32


Open the .ino file in Arduino IDE.

Update your Wi-Fi and MQTT credentials in the code:

const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "broker.mqtt-dashboard.com";


⚠️ Tip: For security, use a secrets.h file and add it to .gitignore before pushing to GitHub.

Connect your ESP32 via USB and select the right board + port.

Upload the code and open the Serial Monitor.

📊 Example Output

Serial Monitor

Connecting to YOUR_WIFI_SSID
WiFi connected
IP address: 192.168.1.25
Hydrogen Level: 245 ppm
Hydrogen Level: 310 ppm


MQTT Topic (sensor/mq8/hydrogen)

Hydrogen Level: 245 ppm
Hydrogen Level: 310 ppm


LCD Display

Hydrogen: 245 ppm

🚀 Future Improvements

Add calibration routine for accurate PPM conversion.

Push data to IoT cloud platforms (ThingsBoard, AWS IoT, Blynk).

Add buzzer/alert for high hydrogen concentration.

📜 License

This project is released under the MIT License – feel free to use, modify, and share.

