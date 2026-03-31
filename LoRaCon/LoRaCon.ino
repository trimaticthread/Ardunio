#include "LoRa_E32.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // Arduino RX <-- E32 TX, Arduino TX --> E32 RX
LoRa_E32 e32ttl(&mySerial);

struct Signal {
  char type[15];
  byte temp[4];
};

unsigned long lastSendTime = 0;
const unsigned long sendInterval = 5000; // 5 saniyede bir gönder

void setup() {
  Serial.begin(9600);
  e32ttl.begin();
  delay(500);
  Serial.println("Start");
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - lastSendTime >= sendInterval) {
    lastSendTime = currentTime;

    Signal data2;

    strncpy(data2.type, "Router 59", sizeof(data2.type));
    data2.type[sizeof(data2.type) - 1] = '\0';

    *(float*)(data2.temp) = 19.2;

    ResponseStatus rs = e32ttl.sendFixedMessage(0, 52, 23, &data2, sizeof(data2));

    Serial.print("Gonderim durumu: ");
    Serial.println(rs.getResponseDescription());
  }
}