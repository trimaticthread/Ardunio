#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int waterSensor = A0;
int waterValue = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  
  pinMode(1, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  waterValue = analogRead(waterSensor);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Level:");
  lcd.setCursor(0, 1);
  lcd.print(waterValue);

  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);

  if (waterValue <= 100) {
    digitalWrite(2, HIGH);
  } else if (waterValue <= 400) {
    digitalWrite(3, HIGH);
  } else if (waterValue <= 700) {
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(5, HIGH);
  }

  delay(500);
}