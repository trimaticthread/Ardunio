#include <Servo.h>

Servo myServo;

void setup() {
  // put your setup code here, to run once:

  myServo.attach(9);

}

void loop() {
  // put your main code here, to run repeatedly:


   for(int pos = 0; pos <= 100; pos++){
    delay(15);
  }

  for(int pos = 100; pos >=0; pos--){
    myServo.write(pos);
    delay(15);
  }
   
}
