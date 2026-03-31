#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const byte ROWS = 4;
const byte COLS = 4;

char keys [ROWS][COLS] = {
    {'1','2','3','A'},
    {'4','5','6','B'},
    {'7','8','9','C'},
    {'*','0','#','D'}
};


byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  // IDE ile haberleşmeyi başlatan komut
Serial.begin(9600);
  
  // LCD Başlatma
  lcd.init();
  lcd.backlight(); 
  lcd.setCursor(0, 0);
  lcd.print("System is Ready to Use...");
  delay(2000);
  lcd.clear();
  lcd.print("Press key:");
}

void loop() {
  char key = keypad.getKey();

  // Eğer bir tuşa basıldıysa (key boş değilse)
  if (key) {
   Serial.print("Pressed: ");
    Serial.println(key);

    // LCD'ye yaz
    lcd.setCursor(0, 1); 
    lcd.print("Key: ");
    lcd.print(key);
    lcd.print("   "); 
  }
}