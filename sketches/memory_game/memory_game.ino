// License: GNU General Public License
// Creation Crate Month 2 - Memory Game

const int button1 = 2;
const int button2 = 3;
const int button3 = 4;
const int button4 = 5;

const int led1 = 7;
const int led2 = 8;
const int led3 = 9;
const int led4 = 5;

const int buzzer = 12;

// Tones for the buzzer using Hertz (Hz)
const int tones[] = { 1900, 1600, 1300, 1000, 3200 };

// These arrays hold 4 values that can either be 1 (button pressed) or 0 (button not pressed)
int buttonState[] = { 0, 0, 0, 0 };     // current state
int lastButtonState[] = { 0, 0, 0, 0 }; // previous state
int buttonCounter[] = { 0, 0, 0, 0 };

// A new game or level starts when gameOn is 0
int gameOn = 0;

// This is used to tell the game to wait until the user inputs a pattern
int wait = 0;

// This is the current game level and the numer of utton presses to make it to the next level
int currentLevel = 1;

// This is the amount of time each LED will flash when the corresponding button is pressed (0.5 seconds)
int ledTime = 500;

// This is the number of levels until the game is won - at which point, the game will get faster
int n_levels = 10;

// This variable will be used to determine which LED to turn and its corresponding buzzer tone
int pinAndTone = 0;

// This value must become 1 to go to the next level
int correct = 0;

// This is the speed of the game.  It increases every time a level is beaten
int speedFactor = 5;

// This is the amount of time taken before the next LED in the pattern lights up (0.2 seconds). 
// This will decrease every time a level is beaten
int ledDelay = 200;

void playTone(int tone, int duration) {
  for(long i = 0; i < duration * 1000L; i+= tone * 2) {
    digitalWrite(buzzer, HIGH); // turns the buzzer on
    delayMicroseconds(tone);    // creates the tone of the buzzer
    digitalWrite(buzzer, LOW);  // turns the buzzer off
    delayMicroseconds(tone);
  }  
}

void setup() {
  // put your setup code here, to run once:
  randomSeed(analogRead(0));  // generate random numbers

  // initialize inputs
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);

  // initialize outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  // stores randomized game pattern
  int n_array[n_levels];

  // stores the pattern input by the user
  int u_array[n_levels];

  int i;

  if(gameOn == 0) {
    for(i = 0; i < n_levels; i += 1) {
      n_array[i] = 0;
      u_array[i] = 0;
      n_array[i] = random(0, 4);  // generates a random pattern
    }

    // the game is ready to run!
    gameOn = 1; 
  }

  // Triggers if no action is required from the user
  if (wait == 0) {
    delay(200);
    i = 0;

    // show the user the current game pattern
    for(i = 0; i < currentLevel; i += 1) {
      ledDelay = ledTime / (1 + (speedFactor / n_levels) * (currentLevel - 1));
      pinAndTone = n_array[i];
      digitalWrite(pinAndTone + 7, HIGH);
      playTone(tones[pinAndTone], ledDelay);
      digitalWrite(pinAndTone + 7, LOW);
      delay(100 / speedFactor);  
    }

    // puts the game on hold until the user enters a pattern
    wait = 1;
  }

  i = 0;

  // detects when a button is pressed
  int buttonChange = 0;

  // current position in the pattern
  int j = 0;

  while(j < currentLevel) {
    while(buttonChange == 0) {

      // determines which button is pressed by the user
      for(i = 0; i < 4; i += 1) {
        buttonState[i] = digitalRead(i + 2);
        buttonChange += buttonState[i];  
      }
    }

    for(i = 0; i < 4; i += 1) {
      if(buttonState[i] == HIGH) {
        // turns the corresponding LED to the button presse, and
        // plays the corresponding sound on the buzzer
        digitalWrite(i + 7, HIGH);
        playTone(tones[i], ledTime);
        digitalWrite(i + 7, LOW);  

        wait = 0;

        // stores the user's input to be matched against the game pattern
        u_array[j] = i; 

        buttonState[i] = LOW;
        buttonChange = 0;
      }
    }

    // checks if the button pressed matches the game pattern
    if(u_array[j] == n_array[j]) {
        j++;
        correct = 1;
    }
    else {
      correct = 0;
      i = 4;
      j = currentLevel;
      wait = 0;
    }    
  }

  // if user makes a mistake reset and start the game over
  if (correct == 0) {
    delay(300); 
    i = 0;
    gameOn = 0;
    currentLevel = 1;

    for(i = 0; i < 4; i += 1) {
      digitalWrite(i + 7, HIGH);
    }

    playTone(tones[4], ledTime);

    for(i = 0; i < 4; i += 1) {
      digitalWrite(i + 7, LOW);  
    }

    delay(200);

    for(i = 0; i < 4; i += 1) {
      digitalWrite(i + 7, HIGH);  
    }

    playTone(tones[4], ledTime);
    
    for(i = 0; i < 4; i += 1) {
      digitalWrite(i + 7, LOW);  
    }

    delay(500);
    gameOn = 0;
  }

  // if user gets the sequence right, the games goes up one level
  if ( correct == 1) {
    currentLevel++;
    wait = 0;
  }

  if ( currentLevel == n_levels) {
    delay(500);
    int notes[] = { 2, 2, 2, 2, 0, 1, 2, 1, 2 };
    int note = 0;
    int tempo[] = { 200, 200, 200, 400, 400, 400, 200, 200, 600 };  
    int breaks[] = { 100, 100, 100, 200, 200, 200, 300, 100, 200 };

    // victory song if the game is beaten
    for(i = 0; i < 9; i += 1) {
      note = notes[i];
      digitalWrite(note + 7, HIGH);
      playTone(tones[note], tempo[i]);
      digitalWrite(note + 7, LOW);
      delay(breaks[i]);
    }

    gameOn = 0;
    currentLevel = 1;
    n_levels = n_levels + 2;

    speedFactor += 1;
  }
}
