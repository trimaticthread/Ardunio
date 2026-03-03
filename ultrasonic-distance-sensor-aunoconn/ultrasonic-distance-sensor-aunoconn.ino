#define trigPin 9
#define echoPin 10


long time;
int distance;

void setup(){
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
  
  
  Serial.begin(9600);
}



void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);
  
  time = pulseIn(echoPin, HIGH);
  distance = time * 0.034 / 2;
  
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm");
  
  delay(500);
  
	  
}
