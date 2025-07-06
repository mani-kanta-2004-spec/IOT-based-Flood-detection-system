#include <Arduino.h>

// Include necessary libraries for ESP32 and WiFi connectivity
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif

#include <ESP_Mail_Client.h>

#define WIFI_SSID "OnePlus Nord 2T 5G"
#define WIFI_PASSWORD "shiva 9999"

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

#define AUTHOR_EMAIL "akarahul67@gmail.com"
#define AUTHOR_PASSWORD "jrqq hlxf qmkq whbk"
#define RECIPIENT_EMAIL "manikantaeerla068@gmail.com"

#define TRIG_PIN 4
#define ECHO_PIN 5
#define FLOW_SENSOR_PIN 18

#define MAX_DISTANCE 20
#define MIN_TRIGGER_INTERVAL 250
#define WATER_LEVEL_THRESHOLD 10

SMTPSession smtp;
Session_Config config;
SMTP_Message message;

unsigned long lastTriggerTime = 0;
int waterLevel = 0;
float flowRate = 0.0;
unsigned long previousMillis = 0;
const unsigned long interval = 1000;
int pulseCount = 0;
float calibrationFactor = 4.5;

void smtpCallback(SMTP_Status status);
void updateFlowRate();

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
  }

  MailClient.networkReconnect(true);
  smtp.debug(1);
  smtp.callback(smtpCallback);

  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;
  config.login.user_domain = "";
  config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  config.time.gmt_offset = 3;
  config.time.day_light_offset = 0;

  message.sender.name = F("ESP32 Water Level and Flow Monitor");
  message.sender.email = AUTHOR_EMAIL;
  message.subject = F("Water Level and Flow Alert!");
  message.addRecipient(F("Water Level and Flow Recipient"), RECIPIENT_EMAIL);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(FLOW_SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(FLOW_SENSOR_PIN), updateFlowRate, RISING);
}

void loop() {
  if (millis() - lastTriggerTime >= MIN_TRIGGER_INTERVAL) {
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);
    long duration = pulseIn(ECHO_PIN, HIGH);
    waterLevel = duration * 0.034 / 2;

    if (waterLevel > WATER_LEVEL_THRESHOLD) {
      String textMsg = "Water level alert! Current flow rate: " + String(flowRate, 2) + " L/min.";
      message.text.content = textMsg.c_str();
      message.text.charSet = "us-ascii";
      message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
      message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
      message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

      if (!smtp.connect(&config)) return;
      if (!MailClient.sendMail(&smtp, &message)) return;

      lastTriggerTime = millis();
    }

    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
      flowRate = (pulseCount * 1000.0 / interval) / calibrationFactor;
      pulseCount = 0;
      previousMillis = currentMillis;
    }
  }
}

void smtpCallback(SMTP_Status status) {
  if (status.success()) {
    for (size_t i = 0; i < smtp.sendingResult.size(); i++) {
      SMTP_Result result = smtp.sendingResult.getItem(i);
    }
    smtp.sendingResult.clear();
  }
}

void updateFlowRate() {
  pulseCount++;
}
