// License: GNU General Public License
// Creation Crate Month 4 - LED Dice Game

#define button 3
#define ledSet1 4
#define ledSet2 5
#define ledSet3 6
#define ledSet4 7

// tracks if the button is on or off
int buttonState;

// stores random number between 1 and 6
int roll;

// 2 seconds
int time = 2000;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledSet1, OUTPUT);
  pinMode(ledSet2, OUTPUT);
  pinMode(ledSet3, OUTPUT);
  pinMode(ledSet4, OUTPUT);
  pinMode(button, INPUT);

  randomSeed(analogRead(0));

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(button);

  if(buttonState == HIGH) {
    roll = random(1, 7);

    if(roll == 1) {
      digitalWrite(ledSet3, HIGH);
    }
    else if(roll == 2) {
      digitalWrite(ledSet1, HIGH);
    }
    else if(roll == 3) {
      digitalWrite(ledSet1, HIGH);
      digitalWrite(ledSet3, HIGH);
    }
    else if(roll == 4) {
      digitalWrite(ledSet2, HIGH);
      digitalWrite(ledSet4, HIGH);
    }
    else if(roll == 5) {      
      digitalWrite(ledSet2, HIGH);
      digitalWrite(ledSet3, HIGH);
      digitalWrite(ledSet4, HIGH);
    }
    else if(roll == 6) {      
      digitalWrite(ledSet1, HIGH);
      digitalWrite(ledSet2, HIGH);
      digitalWrite(ledSet4, HIGH);
    }
  }

  Serial.print("You rolled a ");
  Serial.println(roll);

  delay(time);

  // turn off all the LEDs
  digitalWrite(ledSet1, LOW);
  digitalWrite(ledSet2, LOW);
  digitalWrite(ledSet3, LOW);
  digitalWrite(ledSet4, LOW);
}
