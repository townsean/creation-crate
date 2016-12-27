// Creation Crate Month 6 - 2-Player Reflex Game

int startButton = 8;
int startLED = 9;
int startButtonState = 0;

int p1Button = 4;
int p1LED = 5;
bool p1ButtonState = LOW;
bool p1Finished = false;

int p2Button = 12;
int p2LED = 13;
bool p2ButtonState = LOW;
bool p2Finished = false;

int messageStart = 0;
int gameStart = 0;
int currentTime = 0;
int timeDelay = 0;
int startTime = 0;
int p1EndTime = 0;
int p2EndTime = 0;
bool p1Win = false;
bool p2Win = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // initialize pins
  pinMode(startButton, INPUT);
  pinMode(startLED, OUTPUT);
  pinMode(p1Button, INPUT);
  pinMode(p1LED, OUTPUT);
  pinMode(p2Button, INPUT);
  pinMode(p2LED, OUTPUT);
  Serial.println("Setup complete. Get ready to play!");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(messageStart == 0) {
    Serial.println(" ");
    Serial.println("--------------------------------");
    Serial.println("Press the Start button to begin!");

   // flashing Start LED indicates beginning of gameplay
   flashLED(startLED, 5, 1);

   messageStart = 1;
  }

  startButtonState = digitalRead(startButton);

  if(startButtonState == HIGH && gameStart == 0) {
    startGame();  
  }  
}

void flashLED(int pin, int flashes, int duration) {
  for (int i = 0; i < flashes; i++) {
    digitalWrite(pin, HIGH);
    delay(duration * 1000 / flashes / 2);
    digitalWrite(pin, LOW);
    delay(duration * 1000 / flashes / 2);
  }  
}

void startGame() {
  gameStart = 1;

  // set random interval for the reaction delay
  timeDelay = random(3, 6) * 1000;

  flashLED(startLED, 1, 1);
  Serial.println(" ");
  Serial.println("Fingers ready...");
  flashLED(startLED, 1, 1);
  Serial.println("Set...");
  flashLED(startLED, 1, 1);
  Serial.println("REACT!");
  Serial.println(" ");
  startTime = millis(); // Sets the start time

  while(p1Finished == false || p2Finished == false) {
    p1ButtonState = digitalRead(p1Button);
    p2ButtonState = digitalRead(p2Button);

    currentTime = millis() - startTime;

    if(p1ButtonState == HIGH && p1Finished == false) {
      p1EndTime = millis();
      p1Finished = true;
      Serial.println("Player 1 has finished!");
      Serial.println(" ");
    }

    if(p2ButtonState == HIGH && p2Finished == false) {
      p2EndTime = millis();
      p2Finished = true;
      Serial.println("Player 2 has finished!");
      Serial.println(" ");
    }

    if(currentTime > timeDelay) {
      digitalWrite(startLED, HIGH);
    }
  }

  // Game ended animation
  flashLED(startLED, 5, 1);

  // Calculates the reaction times for p1 and p2
  p1EndTime = p1EndTime - startTime - timeDelay;
  p2EndTime = p2EndTime - startTime - timeDelay;

  // Punishes p1 if they pressed too soon
  if (p1EndTime <= 0) {
    Serial.println("Player 1 pressed too soon!");
    Serial.println(" ");  
  }

  // Punishes p2 if they pressed too soon
  if (p2EndTime <= 0) {
    Serial.println("Player 2 pressed too soon!");
    Serial.println(" ");  
  }

  // Display results
  Serial.println(" ");
  Serial.println("Player 1's reaction time was: ");
  Serial.print(p1EndTime);
  Serial.print(" milliseconds");
  Serial.println(" ");
  Serial.println(" ");
  Serial.println("Player 2's reaction time was: ");
  Serial.print(p2EndTime);
  Serial.print(" milliseconds");
  Serial.println(" ");

  // Player 1 wins
  if(p1EndTime < p2EndTime && p1EndTime > 0) {
    Serial.println(" ");
    Serial.print("Player 1 wins by ");
    Serial.print(p2EndTime - p1EndTime);
    Serial.print(" milliseconds!");
    Serial.println(" ");
    Serial.println(" ");

    flashLED(p1LED, 5, 1);
  }

  // Player 2 wins
  if(p1EndTime > p2EndTime && p2EndTime > 0) {
    Serial.println(" ");
    Serial.print("Player 1 wins by ");
    Serial.print(p2EndTime - p1EndTime);
    Serial.print(" milliseconds!");
    Serial.println(" ");
    Serial.println(" ");

    flashLED(p1LED, 5, 1);
  }

  // if there is a tie
  if (p1EndTime == p2EndTime) {
    Serial.println("Both players tie!!");
    Serial.println(" ");

    flashLED(p1LED, 5, 1);
    flashLED(p2LED, 5, 1);
  }

  p1Finished = 0;
  p2Finished = 0;
  messageStart = 0;
  gameStart = 0;
  delay(1000);
}
