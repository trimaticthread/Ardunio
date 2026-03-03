// I2C LCD + LM35 örneği
// Celsius, Kelvin, Fahrenheit hesaplar ve LED ile durum gösterir.
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LED pinleri
#define LED1_PIN 4
#define LED2_PIN 5

// LM35 sensörü A0 pinine bağlı
const int lm35Pin = A0;
// LCD adresi 0x27, boyut 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // LCD başlat
  lcd.init();
  lcd.backlight();

  // LED pinlerini çıkış yap
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  // Açılış yazısı
  lcd.setCursor(0, 0);
  lcd.print("LM35 C K F");
  delay(1200);
  lcd.clear();
}

void loop() {
  // Analog sensör verisi oku
  // Değer aralığı 0..1023
  int sensorValue = analogRead(lm35Pin);

  // Analog değeri volta çevir
  // voltaj = analog_deger * (5.0 / 1023.0)
  // Neden? Arduino UNO ADC'si 10-bit: 1024 seviye
  float voltage = sensorValue * (5.0 / 1023.0);

  // Sıcaklık dönüşümleri
  // LM35: 10mV = 1°C => sıcaklık = voltaj * 100
  float tempC = voltage * 100.0;

  // Kelvin dönüşümü: K = C + 273.15
  float tempK = tempC + 273.15;

  // Fahrenheit dönüşümü: F = (C * 9/5) + 32
  float tempF = (tempC * 9.0 / 5.0) + 32.0;

  // 1. satır: C ve K göster
  lcd.setCursor(0, 0);
  lcd.print("C:");
  lcd.print(tempC, 1);
  lcd.print(" K:");
  lcd.print(tempK, 1);
  lcd.print(" ");

  // 2. satır: F göster
  lcd.setCursor(0, 1);
  lcd.print("F:");
  lcd.print(tempF, 1);
  lcd.print("        ");

  // Basit kontrol:
  // Sıcaklık 30°C altındaysa LED1 yanar.
  // 30°C ve üstünde LED2 yanar.
  if (tempC < 25.0) {
    digitalWrite(LED1_PIN, HIGH);
    digitalWrite(LED2_PIN, LOW);
  } else {
    digitalWrite(LED1_PIN, LOW  );
    digitalWrite(LED2_PIN, HIGH);
  }

  // Her 1 saniyede ekranı güncelle
  delay(1000);
}
