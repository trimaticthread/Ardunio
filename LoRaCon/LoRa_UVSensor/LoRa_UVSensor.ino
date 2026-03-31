#include "LoRa_E32.h"
#include <SoftwareSerial.h>

#define ROUTER_ID "106"
#define SENSOR_ID "1006"

#define RECIPIENT_ADDH 0
#define RECIPIENT_ADDL 52
#define RECIPIENT_CHANNEL 23

#define SEND_INTERVAL 10000UL 

SoftwareSerial mySerial(10,11); // RX, TX
LoRa_E32 e32ttl(&mySerial);

unsigned long lastSendTime = 0;

struct Payload {
  char router[4];
  char sensor[5];
  char dataKey[4];
  float dataValue;
};

void sendData(const char* key, float value) {
  Payload payload;

  strncpy(payload.router, ROUTER_ID, sizeof(payload.router) - 1);
  payload.router[sizeof(payload.router) - 1] = '\0';

  strncpy(payload.sensor, SENSOR_ID, sizeof(payload.sensor) - 1);
  payload.sensor[sizeof(payload.sensor) - 1] = '\0';

  strncpy(payload.dataKey, key, sizeof(payload.dataKey) - 1);
  payload.dataKey[sizeof(payload.dataKey) - 1] = '\0';

  payload.dataValue = value;

  ResponseStatus rs = e32ttl.sendFixedMessage(
    RECIPIENT_ADDH,
    RECIPIENT_ADDL,
    RECIPIENT_CHANNEL,
    &payload,
    sizeof(payload)
  );

  Serial.print("Gonderilen -> RID: ");
  Serial.print(payload.router);
  Serial.print(" | SID: ");
  Serial.print(payload.sensor);
  Serial.print(" | ");
  Serial.print(payload.dataKey);
  Serial.print(": ");
  Serial.println(payload.dataValue);

  if (rs.code == 1) {
    Serial.println("Sent successfully");
  } else {
    Serial.print("Send failed: ");
    Serial.println(rs.getResponseDescription());
  }
}

void setup() {
  Serial.begin(9600);
  e32ttl.begin();
  delay(500);

  Serial.println("Router started...");
  lastSendTime = millis();
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - lastSendTime >= SEND_INTERVAL) {
    lastSendTime = currentMillis;

    int rawValue = analogRead(A0);

    Serial.print("Raw A0: ");
    Serial.println(rawValue);

    sendData("UV", rawValue);
  }
}