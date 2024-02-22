#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <LiquidCrystal_I2C.h>

#define SUBSCRIBE_TOPIC "test/trimble"
#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2

const char* WIFI_SSID = "brisa-3091372";
const char* WIFI_PASSWORD = "teskdl6u";

const char* mqtt_server = "192.168.0.5";
const int mqtt_port = 1883;
char print_message[32] = "";

WiFiClient espClient;
PubSubClient client(espClient);

LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COLUMNS, LCD_ROWS);

void connect_to_wiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

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
  StaticJsonDocument<256> doc;
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;

  deserializeJson(doc, (const byte*)message, length);
  strlcpy(print_message, doc["print"] | "default", sizeof(print_message));
  
  for (int i = 0; i < length; i++) {
    messageTemp += (char)message[i];
  }

  Serial.println(messageTemp);

  lcd.setCursor(0, 0);

  lcd.print(print_message);
  Serial.println(print_message);
  delay(3000);

  lcd.clear();
}

void reconnect() {

  client.setServer(mqtt_server, mqtt_port);

  while (!client.connected()) {
    Serial.print("Seeking MQTT connection...");

    if (client.connect("ESP32Client")) {
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

  client.setCallback(callback);
  client.subscribe(SUBSCRIBE_TOPIC);
  Serial.print("This client was subcribed at: ");
  Serial.println(SUBSCRIBE_TOPIC);

  lcd.init();
  Serial.println("LCD was initialized");
  
  lcd.backlight(); // turn on the black light
  lcd.noBacklight();
  lcd.backlight();
  lcd.setBacklight(255);
  Serial.println("black light is on");

  lcd.setCursor(0, 0);

  lcd.print("Hello, World!");
  delay(1000);

  lcd.clear();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }

  client.loop();
}