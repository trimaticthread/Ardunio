#define LEDR_PIN_VIN 5

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDR_PIN_VIN, OUTPUT);


}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDR_PIN_VIN, HIGH);
  delay(1000);
  digitalWrite(LEDR_PIN_VIN, HIGH);
  delay(1000);

}
