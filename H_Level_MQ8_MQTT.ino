#include <LiquidCrystal_I2C.h>'
#include <PubSubClient.h>
#include <WiFi.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
const char* ssid = "Satya07";
const char* password = "Satya@1105";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);

long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  lcd.setCursor(0, 0);
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1);
  lcd.print(ssid);
  delay(2000);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    lcd.clear();
    lcd.setCursor(6, 0);
    lcd.print("....");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi connected");
  delay(1000);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    lcd.setCursor(0, 0);

    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);  // ESP32 also supports random()
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      client.publish("H2", "connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      lcd.setCursor(0, 0);
      lcd.print("failed, rc=");
      lcd.setCursor(0, 1);
      lcd.print(client.state());
      lcd.print(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  lcd.begin();  // Initialize LCD
  lcd.backlight();  // Turn on backlight
  for (int x = 0; x <= 20; x++) {
    lcd.setCursor(1, 0);
    lcd.scrollDisplayLeft();
    lcd.print("Welcome to temperature data logger");
    delay(200);
  }
  lcd.clear();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  int hydrogen_value = analogRead(36);  // ADC1 channel 0 (GPIO 36)
  int hydrogen_read = map(hydrogen_value, 0, 4095, 1000, 0);  // ESP32 ADC range is 0-4095
  Serial.print("HYDROGEN LEVEL : ");
  Serial.println(hydrogen_read);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("HYDROGEN LEVEL : ");
  lcd.setCursor(0, 1);
  lcd.print(hydrogen_read);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    snprintf(msg, MSG_BUFFER_SIZE, "%d", hydrogen_read);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("H2", msg);
  }
  delay(10000);
}
