// Tek LED örneği
// Bu pin numarasına bağlı LED'i yakıp söndüreceğiz.
#define LEDR_PIN_VIN 5

void setup() {
  // setup() sadece bir kere çalışır.
  // LED pinini çıkış yapıyoruz, böylece bu pine HIGH/LOW gönderebiliriz.
  pinMode(LEDR_PIN_VIN, OUTPUT);
}

void loop() {
  // loop() sürekli tekrar eder.
  // 1) LED'i yak
  digitalWrite(LEDR_PIN_VIN, HIGH);
  // 1 saniye bekle
  delay(1000);

  // 2) LED'i söndür
  digitalWrite(LEDR_PIN_VIN, LOW);
  // 1 saniye bekle
  delay(1000);
}
