#include <Keypad.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define LED_GREEN 12
#define LED_RED 13

LiquidCrystal_I2C lcd(0x27, 16, 2);

String password = "1234";
String input = "";

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

void resetDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter Password:");
}

void checkPassword() {
  lcd.clear();
  if (input == password) {
    lcd.print("Password Correct");
    digitalWrite(LED_GREEN, HIGH);
    delay(3000); 
    digitalWrite(LED_GREEN, LOW);
  } else {
    lcd.print("Access Denied");
    digitalWrite(LED_RED, HIGH);
    delay(2000);
    digitalWrite(LED_RED, LOW);
  }
  input = ""; 
  resetDisplay();
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  lcd.init();
  lcd.backlight(); 
  resetDisplay();
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    if (key == '#') {
      checkPassword();
    } 
    else if (key == '*') {
      input = "";
      lcd.clear();
      lcd.print("Cleared");
      delay(1000);
      resetDisplay();
    } 
    else {
      input += key;
      lcd.setCursor(input.length() - 1, 1);
      lcd.print("*");
    }
  }
}