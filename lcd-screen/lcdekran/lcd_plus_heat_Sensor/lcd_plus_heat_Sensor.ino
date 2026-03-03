// I2C LCD + LM35 ile sıcaklık gösterimi
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LM35 sensörü A0 pininde
const int lm35Pin = A0;

// LCD adresi: 0x27, boyut: 16 sütun, 2 satır
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // LCD başlat ve arka ışığı aç
  lcd.init();
  lcd.backlight();

  // Üst satıra sabit başlık yaz
  lcd.setCursor(0, 0);
  lcd.print("LM35 Sicaklik");
}

void loop() {
  // Sensörden analog değeri oku
  // analogRead sonucu 0 ile 1023 arasındadır.
  // 0   -> 0V
  // 1023-> yaklaşık 5V (UNO varsayılan referansı)
  int sensorValue = analogRead(lm35Pin);

  // Analog değerini voltaja çevir
  // Neden bu formül?
  // Her adımın voltajı = 5.0 / 1023.0 V
  // Toplam voltaj = okunan_adım * (5.0 / 1023.0)
  // Örnek: 205 okursak voltaj ≈ 205 * 0.004887 = 1.00V
  float voltage = sensorValue * (5.0 / 1023.0);

  // LM35 hesaplama: V * 100 = C
  // Çünkü LM35 sensörü 10mV / 1°C üretir.
  // 10mV = 0.01V olduğuna göre:
  // sıcaklık(°C) = voltaj / 0.01 = voltaj * 100
  // Örnek: 0.30V -> 30°C
  float temperatureC = voltage * 100.0;

  // Alt satıra sıcaklığı yaz
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperatureC, 1);
  lcd.write((uint8_t)223);
  lcd.print("C   ");

  // 1 saniye bekleyip yeni değer göster
  delay(1000);
}
