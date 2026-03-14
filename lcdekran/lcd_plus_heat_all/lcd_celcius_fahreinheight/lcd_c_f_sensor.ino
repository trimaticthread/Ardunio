// I2C LCD ve LM35 sıcaklık sensörü örneği
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// LM35 sensörü A0 pininde
const int lm35Pin = A0;
// LCD adresi: 0x27, boyut: 16x2
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // LCD başlatılır ve ışığı açılır.
  lcd.init();
  lcd.backlight();

  // Açılış ekranı
  lcd.setCursor(0, 0);
  lcd.print("LM35 C/F Sensor");
  delay(1200);
  lcd.clear();
}

void loop() {
  // Analog değeri oku (0 - 1023)
  // 0 -> 0V, 1023 -> yaklaşık 5V
  int sensorValue = analogRead(lm35Pin);

  // Analog değeri volta çevir
  // Formül: voltaj = okunan_deger * (5.0 / 1023.0)
  // Sebep: ADC 10-bit olduğu için 1024 seviye var (0..1023)
  // Örnek: 512 okursan voltaj yaklaşık 2.5V olur
  float voltage = sensorValue * (5.0 / 1023.0);

  // LM35: 10mV = 1°C => V * 100 = °C
  // 0.25V okursak sıcaklık yaklaşık 25°C olur
  float tempC = voltage * 100.0;

  // °C -> °F dönüşümü
  // Formül: F = (C * 9/5) + 32
  float tempF = (tempC * 9.0 / 5.0) + 32.0;

  // 1. satıra Celsius yaz
  lcd.setCursor(0, 0);
  lcd.print("C: ");
  lcd.print(tempC, 1);
  lcd.write((uint8_t)223);
  lcd.print("C   ");

  // 2. satıra Fahrenheit yaz
  lcd.setCursor(0, 1);
  lcd.print("F: ");
  lcd.print(tempF, 1);
  lcd.write((uint8_t)223);
  lcd.print("F   ");

  // Her 1 saniyede bir güncelle
  delay(1000);
}
