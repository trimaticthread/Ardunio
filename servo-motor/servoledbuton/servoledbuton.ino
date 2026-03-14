  #include <Servo.h>

  Servo motor;

  int acmaTusu = 9;
  int kapamaTusu = 8;
  int servoPin = 13;
  int kirmiziLed = 4;
  int yesilLed = 5;

  void setup() {
    motor.attach(servoPin);
    
    pinMode(acmaTusu, INPUT);
    pinMode(kapamaTusu, INPUT);
    pinMode(kirmiziLed, OUTPUT);
    pinMode(yesilLed, OUTPUT);
    
    motor.write(0);
    digitalWrite(kirmiziLed, HIGH);
    digitalWrite(yesilLed, LOW);
  }

  void loop() {
    if (digitalRead(acmaTusu) == HIGH) {
      motor.write(90);
      digitalWrite(yesilLed, HIGH);
      digitalWrite(kirmiziLed, LOW);
    }
    
    if (digitalRead(kapamaTusu) == HIGH) {
      motor.write(0);
      digitalWrite(kirmiziLed, HIGH);
      digitalWrite(yesilLed, LOW);
    }
  }