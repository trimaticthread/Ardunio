// ============================================================
//  Uzaktan Kumanda ile Şifreli Kapı Kontrol Sistemi
//
//  PIN BAĞLANTILARI:
//    IR Alıcı (DATA) → Digital Pin 3   [sol bacak]
//    Kırmızı LED     → Digital Pin 2
//    Yeşil LED       → Digital Pin 4   [Pin 1/TX kullanılamaz!]
//    Servo Motor     → Digital Pin 9
//    LCD I2C         → SDA=A4, SCL=A5  [adres: 0x27, 16x2]
//
//  KUMANDA TUŞLARI:
//    0–9       → Şifre rakamı gir
//    EQ / PLAY / CH+ → Şifreyi onayla
//    CH- / CH / 100+ / 200+ → Girişi sil
// ============================================================

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <IRremote.hpp>

// ---------- PIN T ANIMLARI ----------
// !! UYARI: Pin 0=RX, Pin 1=TX → bu pinlere LED TAKMA!
#define IR_RECEIVE_PIN  3   // IR alıcı data pini  → Digital Pin 3
const int kirmiziLed  = 2;  // Kırmızı LED         → Digital Pin 2
const int yesilLed    = 4;  // Yeşil LED           → Digital Pin 4
const int servoPin    = 9;  // Servo motor         → Digital Pin 9

// ---------- NESNE TANIMLARI ----------
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C adres: 0x27, 16 sütun, 2 satır
Servo kapiServou;                     // Kapı servo motoru

// ---------- ŞİFRE ----------
String sifre = "9966";  // İstediğin 4 haneli şifreyi buraya yaz
String giris = "";      // Kullanıcının girdiği rakamlar burada birikiyor

// ---------- KUMANDA HEX KODLARI ----------
// Bu kodlar kumandana özel — değiştirme!
#define CMD_0       0x68
#define CMD_1       0x30
#define CMD_2       0x18
#define CMD_3       0x7A
#define CMD_4       0x10
#define CMD_5       0x38
#define CMD_6       0x5A
#define CMD_7       0x42
#define CMD_8       0x4A
#define CMD_9       0x52

// Onay tuşları: EQ, PLAY veya CH+
#define CMD_EQ       0x90
#define CMD_PLAY     0xC2
#define CMD_CH_PLUS  0xE2

// Silme tuşları: CH-, CH, 100+, 200+
#define CMD_CH_MINUS  0xA2
#define CMD_CH        0x62
#define CMD_100PLUS   0x98
#define CMD_200PLUS   0xB0


// ============================================================
//  showPasswordScreen(): LCD'ye şifre giriş ekranını yazar
// ============================================================
void showPasswordScreen() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SIFRE GIRINIZ:");
  lcd.setCursor(0, 1);
  lcd.print("                ");  // 2. satırı temizle
}

// ============================================================
//  clearInputLine(): LCD 2. satırını boşaltır
// ============================================================
void clearInputLine() {
  lcd.setCursor(0, 1);
  lcd.print("                ");  // 16 boşluk
}

// ============================================================
//  resetSystem(): Girişi siler, LED'leri söndürür,
//                 şifre ekranını tekrar gösterir
// ============================================================
void resetSystem() {
  giris = "";
  digitalWrite(kirmiziLed, LOW);
  digitalWrite(yesilLed, LOW);
  showPasswordScreen();
}

// ============================================================
//  commandToDigit(): IR komut kodunu rakam karakterine çevirir
//  Tanımsız tuş basılırsa '\0' döner
// ============================================================
char commandToDigit(uint16_t command) {
  switch (command) {
    case CMD_0: return '0';
    case CMD_1: return '1';
    case CMD_2: return '2';
    case CMD_3: return '3';
    case CMD_4: return '4';
    case CMD_5: return '5';
    case CMD_6: return '6';
    case CMD_7: return '7';
    case CMD_8: return '8';
    case CMD_9: return '9';
    default:    return '\0';
  }
}

// EQ, PLAY veya CH+ → şifreyi onayla
bool isConfirmCommand(uint16_t cmd) {
  return (cmd == CMD_EQ || cmd == CMD_PLAY || cmd == CMD_CH_PLUS);
}

// CH-, CH, 100+, 200+ → girişi sil
bool isClearCommand(uint16_t cmd) {
  return (cmd == CMD_CH_MINUS || cmd == CMD_CH || cmd == CMD_100PLUS || cmd == CMD_200PLUS);
}

// ============================================================
//  processPassword(): Girilen şifreyi doğru şifreyle karşılaştırır
//  Doğruysa: Yeşil LED yak, servo 90° aç, 3sn bekle, kapat
//  Yanlışsa: Kırmızı LED yak, 2sn bekle
// ============================================================
void processPassword() {
  lcd.clear();
  lcd.setCursor(0, 0);

  if (giris == sifre) {
    // ---- DOĞRU ŞİFRE ----
    lcd.print("SIFRE DOGRU!");
    digitalWrite(yesilLed, HIGH);    // Yeşil LED'i yak
    digitalWrite(kirmiziLed, LOW);
    kapiServou.write(90);            // Kapıyı aç (90 derece)
    delay(3000);                     // 3 saniye açık kal
    kapiServou.write(0);             // Kapıyı kapat (0 derece)
    delay(1000);

  } else {
    // ---- HATALI ŞİFRE ----
    lcd.print("HATALI SIFRE!");
    digitalWrite(kirmiziLed, HIGH);  // Kırmızı LED'i yak
    digitalWrite(yesilLed, LOW);
    delay(2000);                     // 2 saniye bekle
  }

  resetSystem();  // Her durumda sistemi sıfırla
}


// ============================================================
//  setup(): Arduino açıldığında bir kez çalışır
// ============================================================
void setup() {
  Serial.begin(9600);  // Hata ayıklama için serial açık (Pin 4 = yeşil LED, çakışma yok)

  // LED pinlerini çıkış yap ve söndür
  pinMode(kirmiziLed, OUTPUT);
  pinMode(yesilLed, OUTPUT);
  digitalWrite(kirmiziLed, LOW);
  digitalWrite(yesilLed, LOW);

  // Servo motoru bağla ve başlangıç konumuna getir (kapalı = 0°)
  kapiServou.attach(servoPin);
  kapiServou.write(0);

  // LCD'yi başlat ve arka ışığı aç
  lcd.init();
  lcd.backlight();

  // Şifre giriş ekranını göster
  resetSystem();

  // IR alıcıyı başlat (ENABLE_LED_FEEDBACK → Pin 13 dahili LED'i kullanır, sorun yok)
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.println("=== Sistem Hazir ===");
  Serial.println("Kumandadan rakam gir, EQ/PLAY/CH+ ile onayla.");
}


// ============================================================
//  loop(): Sürekli tekrar eden ana döngü
// ============================================================
void loop() {
  // IR alıcıda sinyal var mı?
  if (IrReceiver.decode()) {

    // Tekrar sinyali filtrele (tuşa basılı tutulduğunda oluşur)
    if (!(IrReceiver.decodedIRData.flags & IRDATA_FLAGS_IS_REPEAT)) {

      uint16_t cmd = IrReceiver.decodedIRData.command;

      // Hata ayıklama: Basılan tuşun HEX kodunu Serial'a yaz
      Serial.print("Basilan tus (HEX): 0x");
      Serial.println(cmd, HEX);

      char rakam = commandToDigit(cmd);

      if (rakam != '\0') {
        // ---- Rakam tuşu basıldı ----
        if (giris.length() >= 4) {
          // 4 hane doluysa otomatik sıfırla ve yeniden başla
          giris = "";
          clearInputLine();
        }
        giris += rakam;
        // LCD 2. satırında girilen her rakamı '*' ile göster (güvenlik)
        lcd.setCursor(giris.length() - 1, 1);
        lcd.print("*");

      } else if (isClearCommand(cmd)) {
        // ---- Silme tuşu basıldı ----
        giris = "";
        clearInputLine();

      } else if (isConfirmCommand(cmd)) {
        // ---- Onay tuşu basıldı ----
        processPassword();
      }
    }

    // Bir sonraki IR sinyali için alıcıyı hazırla
    IrReceiver.resume();
  }
}