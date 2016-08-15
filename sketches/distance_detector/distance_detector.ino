// License: GNU General Public License
// Creation Crate Month 3 - Distance Detector

#define red2 13
#define red1 12
#define yellow2 11
#define yellow1 10
#define white2 9
#define white1 8
#define buzzer 3
#define trigPin 7
#define echoPin 6

int sound = 250;
long duration, distance;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(white1, OUTPUT);
  pinMode(white2, OUTPUT);
  pinMode(yellow1, OUTPUT);
  pinMode(yellow2, OUTPUT);
  pinMode(red1, OUTPUT);
  pinMode(red2, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // send out pulse waves for measuring the distance of an object
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // the amount of time it took for the pulse to return
  duration = pulseIn(echoPin, HIGH);

  // distance in cm
  distance = duration / 58.2; //(duration / 2) / 29.1;

  // manipulate leds based on distance calculated
  if (distance <= 40) {
    digitalWrite(white1, HIGH);
    sound = 900;
  }
  else {
    digitalWrite(white1, LOW);
  }

  if (distance < 30) {
    digitalWrite(white2, HIGH);
    sound = 1000;
  }
  else {
    digitalWrite(white2, LOW);
  }

  if (distance < 20) {
    digitalWrite(yellow1, HIGH);
    sound = 1100;
  }
  else {
    digitalWrite(yellow1, LOW);
  }

  if (distance < 15) {
    digitalWrite(yellow2, HIGH);
    sound = 1200;
  }
  else {
    digitalWrite(yellow2, LOW);
  }

  if (distance < 10) {
    digitalWrite(red1, HIGH);
    sound = 1300;
  }
  else {
    digitalWrite(red1, LOW);
  }

  if (distance < 5) {
    digitalWrite(red2, HIGH);
    sound = 1400;
  }
  else {
    digitalWrite(red2, LOW);
  }

  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.print(", ");
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(", ");

  // if object is too far, turn buzzer off
  if (distance > 40 || distance <= 0) {
    Serial.println("Out of range");
    noTone(buzzer);  
  }
  else {
    Serial.println("in");
    tone(buzzer, sound);
  }

  delay(500);
}
