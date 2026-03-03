// Ultrasonik mesafe sensörü örneği (HC-SR04 gibi)
// trigPin: sensöre ölçüm başlat komutu gider.
// echoPin: sensörden geri dönen sinyal okunur.
#define trigPin 9
#define echoPin 10

// time: echo sinyalinin süresi (mikrosaniye)
// distance: hesaplanan mesafe (cm)
long time;
int distance;

void setup(){
  // trig çıkış, echo giriş olmalı.
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Sonuçları seri monitörde görmek için başlatıyoruz.
  Serial.begin(9600);
}

void loop(){
  // Önce trig pinini kısa süre LOW yaparak temiz başlangıç ver.
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // 10 mikro saniyeye yakın bir HIGH darbesi göndererek ölçümü başlat.
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Echo pininin HIGH kaldığı süreyi oku.
  time = pulseIn(echoPin, HIGH);

  // Mesafe formülü:
  // distance = süre * ses_hızı / 2
  // 0.034 cm/us yaklaşık ses hızıdır (hava, oda sıcaklığı).
  // /2 yapmamızın sebebi: sinyal gidip geri dönüyor.
  // Yani ölçtüğümüz süre, tek yön değil gidiş+dönüş süresi.
  // Örnek: süre 1000us ise mesafe ≈ 1000 * 0.034 / 2 = 17cm
  distance = time * 0.034 / 2;

  // Sonucu seri monitöre yazdır.
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Yarım saniye bekleyip yeni ölçüme geç.
  delay(500);
}
