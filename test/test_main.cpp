#include <Arduino.h>
#include <unity.h>
#include <Wire.h>
#include <WiFi.h>

#define LCD_ADDRESS 0x27
#define LCD_COLUMNS 16
#define LCD_ROWS 2
#define WIFI_IS_CONNECTED 1

const char* WIFI_SSID = "brisa-3091372";
const char* WIFI_PASSWORD = "teskdl6u";

void setUp(void)
{
  // set stuff up here
}

void tearDown(void)
{
  // clean stuff up here
}

void test_lcd_address(void) {
  byte error, address;
  int nDevices = 0;
  String lcd_address = "";

  for (address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0 || error == 4) {
      if (address < 16) {
        lcd_address += "0";
      }
      lcd_address += String(address, HEX);
      nDevices++;
      break;
    }
  }

  TEST_ASSERT_EQUAL_STRING(String(LCD_ADDRESS, HEX).c_str(), lcd_address.c_str());
}

void test_wifi_connected(void) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int wifi_timeout = 0;
  int wifi_connected = 0;

  while (WiFi.status() != WL_CONNECTED && wifi_timeout <= 5) {
    delay(1000);
    wifi_timeout++;

    if (WiFi.status() == WL_CONNECTED) {
      wifi_connected = 1;
    }

  }

  TEST_ASSERT_EQUAL_INT(WIFI_IS_CONNECTED, wifi_connected);
}

void setup()
{
  Serial.begin(115200);
  Wire.begin();
  delay(2000);

  UNITY_BEGIN(); // IMPORTANT LINE!
}

void loop()
{
  RUN_TEST(test_lcd_address);
  delay(500);

  RUN_TEST(test_wifi_connected);
  delay(500);

  UNITY_END(); // stop unit testing
}