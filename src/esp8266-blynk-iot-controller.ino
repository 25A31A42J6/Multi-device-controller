#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "secrets.h"

#define LED_PIN    2    // D4 / GPIO2
#define BUZZER_PIN 14   // D5 / GPIO14
#define RELAY_PIN  12   // D6 / GPIO12

// Confirm relay trigger polarity for your specific module.
#define RELAY_ON  LOW
#define RELAY_OFF HIGH

unsigned long lastBlynkAttempt = 0;
unsigned long lastWiFiAttempt = 0;

BLYNK_WRITE(V0)
{
  digitalWrite(LED_PIN, param.asInt() ? HIGH : LOW);
}

BLYNK_WRITE(V1)
{
  int value = param.asInt();
  digitalWrite(BUZZER_PIN, value ? HIGH : LOW);
  Serial.print("Buzzer: ");
  Serial.println(value ? "ON" : "OFF");
}

BLYNK_WRITE(V2)
{
  int value = param.asInt();
  digitalWrite(RELAY_PIN, value ? RELAY_ON : RELAY_OFF);
}

BLYNK_CONNECTED()
{
  digitalWrite(RELAY_PIN, RELAY_OFF);
  Blynk.virtualWrite(V2, 0);
  Serial.println("Blynk connected!");
}

void setup()
{
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, RELAY_OFF);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);

  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Wi-Fi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Blynk.config(BLYNK_AUTH_TOKEN);
  Serial.println("Connecting to Blynk...");

  if (!Blynk.connect(10000))
  {
    Serial.println("Initial Blynk connection failed; retries will continue.");
  }
}

void loop()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    if (millis() - lastWiFiAttempt >= 10000)
    {
      lastWiFiAttempt = millis();
      Serial.println("Wi-Fi disconnected. Reconnecting...");
      WiFi.disconnect();
      WiFi.begin(ssid, pass);
    }
    return;
  }

  if (Blynk.connected())
  {
    Blynk.run();
  }
  else if (millis() - lastBlynkAttempt >= 5000)
  {
    lastBlynkAttempt = millis();
    Serial.println("Retrying Blynk connection...");
    if (Blynk.connect(1000))
    {
      Serial.println("Blynk reconnected!");
    }
    else
    {
      Serial.println("Blynk still disconnected.");
    }
  }
}
