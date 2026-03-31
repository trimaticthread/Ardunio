#include "LoRa_E32.h"
#include <SoftwareSerial.h>

#define ROUTER_ID "105"
#define SENSOR_ID "1005"

#define SEND_INTERVAL 10000UL
#define MQ_PIN A0

// RECEIVER AYARLARI
#define RECEIVER_ADDH 0
#define RECEIVER_ADDL 52
#define RECEIVER_CHANNEL 23

SoftwareSerial mySerial(10, 11); // RX, TX
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
        RECEIVER_ADDH,
        RECEIVER_ADDL,
        RECEIVER_CHANNEL,
        &payload,
        sizeof(payload)
    );

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

    pinMode(MQ_PIN, INPUT);

    delay(500);

    Serial.println("Router started...");
    lastSendTime = millis();
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - lastSendTime >= SEND_INTERVAL) {
        lastSendTime = currentMillis;

        int gasValue = analogRead(MQ_PIN);
        float concentration = map(gasValue, 0, 1023, 0, 1000);

        Serial.print("Gas: ");
        Serial.println(gasValue);

        Serial.print("Concentration: ");
        Serial.println(concentration);

        sendData("GAS", gasValue);
        delay(100);

        sendData("CON", concentration);
    }
}