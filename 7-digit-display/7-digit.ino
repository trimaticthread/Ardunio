// 7-segment display pin eşleşmeleri
// A,B,C,D,E,F,G segmentleri ve DP (nokta)
#define SEG_A  2
#define SEG_B  3
#define SEG_C  4
#define SEG_D  5
#define SEG_E  6
#define SEG_F  7
#define SEG_G  8
#define SEG_DP  9

// Bu fonksiyon verilen rakamı (0-9) ekranda gösterir.
void showDigit(int digit);

void setup() {
  // setup() sadece bir kez çalışır.
  // Tüm segment pinlerini çıkış yapıyoruz.
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_DP, OUTPUT);

  // Nokta (DP) başlangıçta kapalı olsun.
  digitalWrite(SEG_DP, LOW);
}

void loop() {
  // 0'dan 9'a kadar tüm rakamları sırayla göster.
  for (int i = 0; i <= 9; i++) {
    showDigit(i);
    // Her rakam 1 saniye görünsün.
    delay(1000);
  }
}

void showDigit(int digit) {
  // Yeni rakamı yazmadan önce tüm segmentleri kapat.
  digitalWrite(SEG_A, LOW);
  digitalWrite(SEG_B, LOW);
  digitalWrite(SEG_C, LOW);
  digitalWrite(SEG_D, LOW);
  digitalWrite(SEG_E, LOW);
  digitalWrite(SEG_F, LOW);
  digitalWrite(SEG_G, LOW);
  digitalWrite(SEG_DP, LOW);

  // Hangi rakam ise o rakama ait segmentleri yak.
  switch (digit) {
    case 0:
      // 0 için: A,B,C,D,E,F açık, G kapalı
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH);
      digitalWrite(SEG_F, HIGH);
      break;

    case 1:
      // 1 için: B,C
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      break;

    case 2:
      // 2 için: A,B,D,E,G
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH);
      digitalWrite(SEG_G, HIGH);
      break;

    case 3:
      // 3 için: A,B,C,D,G
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_G, HIGH);
      break;

    case 4:
      // 4 için: B,C,F,G
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_F, HIGH);
      digitalWrite(SEG_G, HIGH);
      break;

    case 5:
      // 5 için: A,C,D,F,G
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_F, HIGH);
      digitalWrite(SEG_G, HIGH);
      break;

    case 6:
      // 6 için: A,C,D,E,F,G
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH);
      digitalWrite(SEG_F, HIGH);
      digitalWrite(SEG_G, HIGH);
      break;

    case 7:
      // 7 için: A,B,C
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      break;

    case 8:
      // 8 için: tüm segmentler açık
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_E, HIGH);
      digitalWrite(SEG_F, HIGH);
      digitalWrite(SEG_G, HIGH);
      break;

    case 9:
      // 9 için: A,B,C,D,F,G
      digitalWrite(SEG_A, HIGH);
      digitalWrite(SEG_B, HIGH);
      digitalWrite(SEG_C, HIGH);
      digitalWrite(SEG_D, HIGH);
      digitalWrite(SEG_F, HIGH);
      digitalWrite(SEG_G, HIGH);
      break;

    default:
      // Geçersiz bir sayı gelirse hiçbir şey yapma.
      break;
  }
}

