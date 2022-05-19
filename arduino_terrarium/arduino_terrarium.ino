/**************************************************************************************************/
// Example: echobot
// Description:
//   Bot that response to any received text message with the same text received (echo messages).
//   It gives you a basic idea of how to receive and send messages.
// Created on: 21 apr. 2019
// Last modified date: 21 apr. 2019
// Version: 1.0.0
/**************************************************************************************************/
// OTA update wi-fi
#include <ArduinoOTA.h>
#include <WiFiUdp.h>
#include <GyverNTC.h>
#include <string.h>
#include <Arduino.h>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
// Custom libraries
#include <utlgbotlib.h>
#include <LiquidCrystal_I2C.h>
#include <NTPClient.h> // Time Libraries

/* Libraries */

// Time Libraries
const long utcOffsetInSeconds = 3600;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// Определение NTP-клиента для получения времени
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "by.pool.ntp.org", utcOffsetInSeconds);

// термистор на пине А0
// сопротивление резистора 10к
// тепловой коэффициент 3950
GyverNTC therm(0, 10000, 3950);

// Standard C/C++ libraries
// Device libraries (Arduino ESP32/ESP8266 Cores)

LiquidCrystal_I2C lcd(0x27, 16, 2); // Устанавливаем дисплей

/**************************************************************************************************/

// WiFi Parameters
#define WIFI_SSID "SSID"
#define WIFI_PASS "PASS"
#define MAX_CONN_FAIL 50
#define MAX_LENGTH_WIFI_SSID 31
#define MAX_LENGTH_WIFI_PASS 63

// Telegram Bot Token (Get from Botfather)
#define TLG_TOKEN "telegram_api_key"

// Enable Bot debug level (0 - None; 1 - Bot Level; 2 - Bot+HTTPS Level)
#define DEBUG_LEVEL_UTLGBOT 0

/**************************************************************************************************/

/* Functions Prototypes */

void wifi_init_stat(void);
bool wifi_handle_connection(void);

/**************************************************************************************************/

/* Globals */

// Create Bot object
uTLGBot Bot(TLG_TOKEN);

/**************************************************************************************************/

/* Main Function */
int relayPin = 14; // GPIO0 of ESP8266
int relayPinStat = 12; // GPIO0 of ESP8266
int relayPinLight = 13; // GPIO0 of ESP8266

int value = HIGH;
int status = 0;

void setup(void)
{
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  pinMode(relayPinStat, OUTPUT);
  digitalWrite(relayPinStat, LOW);
  pinMode(relayPinLight, OUTPUT);
  digitalWrite(relayPinLight, LOW);

  // Enable Bot debug
  Bot.set_debug(DEBUG_LEVEL_UTLGBOT);

  // Initialize Serial
  Serial.begin(115200);

  // Initialize WiFi station connection
  wifi_init_stat();

  // Wait WiFi connection
  Serial.println("Waiting for WiFi connection.");
  while (!wifi_handle_connection())
  {
    Serial.println(".");
    delay(1000);
  }

  // Bot getMe command
  Bot.getMe();

  // Display I2c
  lcd.init();
  lcd.backlight();// Включаем подсветку дисплея
  // Display I2c

  // OTA wi-fi update
  // OTA wi-fi update
  // OTA wi-fi update
  // OTA wi-fi update

  // Port defaults to 8266
  // ArduinoOTA.setPort(8266);

  // Hostname defaults to esp8266-[ChipID]
  // ArduinoOTA.setHostname("myesp8266");

  // No authentication by default
  // ArduinoOTA.setPassword("admin");

  // Password can be set with it's md5 value as well
  // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
  // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // OTA wi-fi update
  // OTA wi-fi update
  // OTA wi-fi update
  // OTA wi-fi update
  // OTA wi-fi update

  // Time Libraries
  timeClient.begin();
}

void loop()
{
  timeClient.update();

  // OTA wi-fi update
  ArduinoOTA.handle();
  // OTA wi-fi update

  temperature();

  // Check if WiFi is connected
  if (!wifi_handle_connection())
  {
    // Wait 100ms and check again
    delay(100);
    return;
  }

  // Test Bot getUpdate command and receive messages
  while (Bot.getUpdates())
  {
    telegramMSG();
    // Feed the Watchdog
    yield();
  }

  // Wait 1s for next iteration
  delay(100);
}
