# Arduino Çalışma Koleksiyonu (Detaylı Setup + Proje Rehberi)

Bu depo, Arduino ile temel elektronik ve sensör kullanımını adım adım öğrenmek için hazırlanmış bir çalışma setidir.
Odak nokta: **sade kod, anlaşılır mantık, hızlı test**.

---

## 1) İçindekiler

- [1) İçindekiler](#1-i̇çindekiler)
- [2) Proje Yapısı](#2-proje-yapısı)
- [3) Ön Koşullar](#3-ön-koşullar)
- [4) Hızlı Başlangıç (5 Dakika)](#4-hızlı-başlangıç-5-dakika)
- [5) Donanım Kurulum Detayı](#5-donanım-kurulum-detayı)
- [6) Klasör Bazlı Projeler ve Mantıkları](#6-klasör-bazlı-projeler-ve-mantıkları)
- [7) LCD + LM35 Formül Açıklamaları (Sınavlık)](#7-lcd--lm35-formül-açıklamaları-sınavlık)
- [8) Seri Monitör / Ölçüm Doğrulama](#8-seri-monitör--ölçüm-doğrulama)
- [9) Sık Hata ve Çözüm Rehberi](#9-sık-hata-ve-çözüm-rehberi)
- [10) Kodlama Standardı (Bu Depoda)](#10-kodlama-standardı-bu-depoda)
- [11) Geliştirme Önerileri](#11-geliştirme-önerileri)
- [12) Kısa Sınav Kopya Notu (Temiz Ezber)](#12-kısa-sınav-kopya-notu-temiz-ezber)

---

## 2) Proje Yapısı

```text
Arduino/
├─ 7-digit-display/
│  └─ 7-digit.ino
├─ lcd-screen/
│  └─ lcdekran/
│     ├─ lcdekran.ino
│     ├─ lcd_c_f_sensor/
│     │  └─ lcd_c_f_sensor.ino
│     ├─ lcd_c_k_f_sensor/
│     │  └─ lcd_c_k_f_sensor.ino
│     └─ lcd_plus_heat_Sensor/
│        └─ lcd_plus_heat_Sensor.ino
├─ libraries/
│  └─ LiquidCrystal_I2C/
│     ├─ LiquidCrystal_I2C.cpp
│     ├─ LiquidCrystal_I2C.h
│     └─ ...
├─ one-light-blink/
│  └─ one-light-blink.ino
├─ two-light-sametimeblink/
│  └─ two-light-sametimeblink.ino
└─ ultrasonic-distance-sensor-aunoconn/
   └─ ultrasonic-distance-sensor-aunoconn.ino
```

---

## 3) Ön Koşullar

### 3.1 Donanım

- Arduino UNO (veya UNO uyumlu kart)
- USB kablo
- Breadboard
- Jumper kablo (male-male)
- LED (en az 3 adet)
- 220Ω direnç (her LED için)
- HC-SR04 ultrasonik sensör (veya benzer)
- LM35 sıcaklık sensörü
- I2C 16x2 LCD (genelde adres `0x27`)
- 7-segment display (common cathode varsayımıyla test edildi)

### 3.2 Yazılım

- Arduino IDE 2.x **veya** VS Code + Arduino eklentisi
- Uygun kart sürücüleri (CH340/CP210x gerekebilir)

### 3.3 Kütüphane

Bu depoda `libraries/LiquidCrystal_I2C` mevcut. Arduino IDE’nin görmesi için iki seçenek var:

1. Arduino IDE > Sketch > Include Library > Add .ZIP Library (zip’leyip ekleme)
2. `LiquidCrystal_I2C` klasörünü Arduino `libraries` klasörüne kopyalama

Windows varsayılan yol örneği:

`C:\Users\<kullanici>\Documents\Arduino\libraries\`

---

## 4) Hızlı Başlangıç (5 Dakika)

1. Arduino IDE’yi aç.
2. Kartı seç: **Tools > Board > Arduino UNO**
3. COM port seç: **Tools > Port > COMx**
4. Çalıştırmak istediğin `.ino` dosyasını aç.
5. Verify (✔) ile derle.
6. Upload (→) ile karta yükle.
7. Gerekliyse Serial Monitor aç (9600 baud).

> Not: Her klasör bağımsız bir sketch’tir. Aynı anda tek sketch yüklenir.

---

## 5) Donanım Kurulum Detayı

### 5.1 LED bağlantı kuralı

- Arduino dijital pin -> 220Ω direnç -> LED anodu (+)
- LED katodu (-) -> GND

### 5.2 HC-SR04 (Ultrasonik) bağlantısı

- VCC -> 5V
- GND -> GND
- TRIG -> D9
- ECHO -> D10

### 5.3 LM35 bağlantısı (düz yüz sana bakarken)

- Sol pin -> +5V
- Orta pin -> A0 (analog giriş)
- Sağ pin -> GND

### 5.4 I2C LCD bağlantısı

- VCC -> 5V
- GND -> GND
- SDA -> A4 (UNO)
- SCL -> A5 (UNO)

### 5.5 7-Segment bağlantısı (mevcut koda göre)

- A -> D2
- B -> D3
- C -> D4
- D -> D5
- E -> D6
- F -> D7
- G -> D8
- DP -> D9

> Önemli: 7-segment tipine göre HIGH/LOW mantığı değişebilir.
> Bu kod **common cathode** mantığına göre yazılmıştır.

---

## 6) Klasör Bazlı Projeler ve Mantıkları

### 6.1 `one-light-blink/one-light-blink.ino`

Amaç:
- Tek LED’i 1 saniye açık / 1 saniye kapalı yanıp söndürmek.

Mantık:
- `setup()` içinde LED pini `OUTPUT` yapılır.
- `loop()` içinde `HIGH -> delay -> LOW -> delay` döngüsü çalışır.

Beklenen sonuç:
- LED sabit periyotla blink eder.

---

### 6.2 `two-light-sametimeblink/two-light-sametimeblink.ino`

Amaç:
- 3 LED’i sırayla yakmak (LED1, sonra LED2, sonra LED3).

Mantık:
- Her adımda bir LED `HIGH`, diğerleri `LOW`.
- Her adım arası `delay(1000)`.

Beklenen sonuç:
- “Kayan ışık” benzeri basit sekans.

---

### 6.3 `ultrasonic-distance-sensor-aunoconn/ultrasonic-distance-sensor-aunoconn.ino`

Amaç:
- Ultrasonik sensörle mesafe ölçüp seri monitöre cm cinsinden yazdırmak.

Mantık:
1. TRIG pinine kısa tetik darbesi gönderilir.
2. ECHO pinindeki HIGH süresi okunur (`pulseIn`).
3. Süre, mesafeye çevrilir:
   - `distance = time * 0.034 / 2`

Neden `/2`?
- Ses dalgası hedefe gider ve geri döner.
- Ölçülen süre gidiş+dönüş süresi olduğu için yarıya bölünür.

Beklenen sonuç:
- Serial Monitor’da periyodik `Distance: xx cm` çıktısı.

---

### 6.4 `7-digit-display/7-digit.ino`

Amaç:
- 7-segment üzerinde 0’dan 9’a kadar rakamları göstermek.

Mantık:
- Önce tüm segmentler kapatılır.
- `switch-case` ile ilgili rakamın segmentleri açılır.

Beklenen sonuç:
- Her 1 saniyede bir sonraki rakama geçiş.

Not:
- Segment sıralaması (A-G) doğru bağlanmazsa rakamlar yanlış görünür.

---

### 6.5 `lcd-screen/lcdekran/lcd_plus_heat_Sensor/lcd_plus_heat_Sensor.ino`

Amaç:
- LM35’ten sıcaklık okuyup LCD’de Celsius gösterimi yapmak.

Mantık:
1. `analogRead(A0)` ile 0..1023 değer alınır.
2. Voltaja çevrilir: `voltage = raw * (5.0 / 1023.0)`
3. Celsius: `tempC = voltage * 100`
4. LCD alt satırda gösterilir.

Beklenen sonuç:
- LCD’de periyodik sıcaklık güncellemesi.

---

### 6.6 `lcd-screen/lcdekran/lcd_c_f_sensor/lcd_c_f_sensor.ino`

Amaç:
- Sıcaklığı hem Celsius hem Fahrenheit olarak LCD’de göstermek.

Ek formül:
- `F = (C * 9/5) + 32`

Beklenen sonuç:
- 1. satır `C`, 2. satır `F` bilgisi.

---

### 6.7 `lcd-screen/lcdekran/lcd_c_k_f_sensor/lcd_c_k_f_sensor.ino`

Amaç:
- Celsius, Kelvin, Fahrenheit değerlerini aynı ekranda göstermek.
- Eşik üstü/altı için LED durum göstergesi vermek.

Formüller:
- `K = C + 273.15`
- `F = (C * 9/5) + 32`

Not:
- Güncel kodda LED eşiği `25.0°C` olarak ayarlı.

Beklenen sonuç:
- `tempC < 25.0` ise LED1 yanar, değilse LED2 yanar.

---

## 7) LCD + LM35 Formül Açıklamaları (Sınavlık)

### 7.1 ADC neden 1023?

Arduino UNO ADC’si 10-bit çözünürlüktedir.

- 10-bit => 1024 seviye
- sayım aralığı => `0..1023`

### 7.2 Voltaj formülü

`voltage = raw * (Vref / 1023.0)`

- UNO varsayılan `Vref` genelde 5.0V
- örnek: `raw = 205`
- `V ≈ 205 * (5/1023) ≈ 1.00V`

### 7.3 LM35 sıcaklık formülü

LM35: `10mV = 1°C` yani `0.01V = 1°C`

`tempC = voltage / 0.01 = voltage * 100`

### 7.4 Sınavda sabit nasıl ezberlenir?

UNO için birleştirilmiş sabit:

`tempC = raw * (5.0 * 100 / 1023.0)`

`5*100/1023 = 0.48876`

Yani kısa yol:

`tempC ≈ raw * 0.48876`

Eğer `Vref` 1.1V ise:

`tempC = raw * (1.1*100/1023) = raw * 0.1075`

---

## 8) Seri Monitör / Ölçüm Doğrulama

### Ultrasonik için

- Baud: `9600`
- Nesneyi yaklaştır/uzaklaştır
- Değerin mantıklı değiştiğini doğrula

### LM35 için

- Sensöre parmakla temas et
- 5-10 saniyede sıcaklıkta artış gözlenmeli
- Ani sıçrama varsa kablo ve GND ortaklığını kontrol et

---

## 9) Sık Hata ve Çözüm Rehberi

### 9.1 LCD hiç yazmıyor

- I2C adresi yanlış olabilir (`0x27` yerine `0x3F` deneyin)
- SDA/SCL pinleri yanlış olabilir
- GND/VCC ters olabilir

### 9.2 Derleme hatası: `LiquidCrystal_I2C.h: No such file`

- Kütüphane IDE’ye düzgün eklenmemiştir
- `libraries` klasör yolunu kontrol edin

### 9.3 Ultrasonik sürekli 0 veya saçma değer veriyor

- TRIG/ECHO pinleri karışmış olabilir
- GND ortak değilse ölçüm bozulur
- Hedef çok yakın/çok uzak olabilir

### 9.4 7-segment yanlış rakam gösteriyor

- Segment pin sırası kod ile uyuşmuyor olabilir
- Common anode/cathode tipi kodla uyumsuz olabilir

### 9.5 LED hiç yanmıyor

- Direnç veya LED yönü ters olabilir
- Pin numarası koddan farklı bağlanmış olabilir

---

## 10) Kodlama Standardı (Bu Depoda)

- Her sketch tek amaca odaklı
- Kod adımları açıklayıcı yorumlarla destekli
- `setup()` sadece başlangıç ayarları
- `loop()` tekrar eden davranış
- Hesaplama formülleri yorumda gerekçesiyle belirtilir

---

## 11) Geliştirme Önerileri

- `const` kullanımıyla sabitleri merkezileştir
- `delay()` yerine `millis()` ile non-blocking akış dene
- LCD için “değer değiştiyse yaz” mantığı ekle
- Ölçümde hareketli ortalama (filter) uygula
- 7-segment için dizi tabanlı segment haritasına geç

---

## 12) Kısa Sınav Kopya Notu (Temiz Ezber)

- ADC: `raw = analogRead(A0)` -> `0..1023`
- Voltaj: `V = raw * (Vref / 1023.0)`
- LM35 Celsius: `C = V * 100`
- Fahrenheit: `F = (C*9/5)+32`
- Kelvin: `K = C + 273.15`
- Ultrasonik: `cm = us * 0.034 / 2`

---

## Ek Not

Bu depo eğitim odaklıdır. Kodlar “okunabilirlik ve temel mantığı gösterme” önceliğiyle tutulmuştur.
Gerçek projede hata toleransı, filtreleme, kalibrasyon ve güvenlik kontrolleri eklenmelidir.
