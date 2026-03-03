// 3 LED sırayla yanma örneği
// Her adımda sadece bir LED yanacak.
#define LED1_PIN 5
#define LED2_PIN 6
#define LED3_PIN 7

void setup() {
  // setup() sadece bir kere çalışır.
  // Tüm LED pinlerini çıkış yapıyoruz.
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);
}

void loop() {
  // 1. adım: LED1 açık, diğerleri kapalı
  digitalWrite(LED1_PIN, HIGH);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);
  delay(1000);

  // 2. adım: LED2 açık, diğerleri kapalı
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, HIGH);
  digitalWrite(LED3_PIN, LOW);
  delay(1000);

  // 3. adım: LED3 açık, diğerleri kapalı
  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, HIGH);
  delay(1000);
}
