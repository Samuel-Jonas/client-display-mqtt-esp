#include <Arduino.h>
#include "Display_LCD_I2C_HAL.h"
#include <WiFi.h>
#include <PubSubClient.h>

#define SUBSCRIBE_TOPIC "test/trimble"

// Replace the next variables with your SSID/Password combination
const char* ssid = "REPLACE_WITH_YOUR_SSID";
const char* password = "REPLACE_WITH_YOUR_PASSWORD";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = broker IP device runing in another esp;
const char* mqtt_server = "YOUR_MQTT_BROKER_IP_ADDRESS";

WiFiClient espClient;
PubSubClient client(espClient);

Display_LCD_I2C lcd(LCD_DISPLAY_ADDRESS, LCD_DISPLAY_COLUMNS, LCD_DISPLAY_ROWS);

void connect_to_wiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.print(" done!\n");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }

  Serial.println(messageTemp);

  lcd.setCursor(0, 0);

  lcd.print(messageTemp);
  delay(1000);

  lcd.clear();
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Seeking MQTT connection...");

    if (client.connect("ESP32")) {
      Serial.println("connected");

      client.subscribe("test/trimble");
    } else {
      Serial.print("failed, client state=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  connect_to_wiFi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  client.subscribe("test/trimble");

  lcd.begin(); //initialize
  
  lcd.backlight(); // turn on the black light
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}


