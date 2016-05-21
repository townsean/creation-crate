// License: GNU General Public License
// Creation Crate: Month 1 - Mood Lamp

int pulseSpeed = 1;
int ldrPin = 0; // LDR (Light Dependent Resistor) in Analog 0
int redLed = 11;
int greenLed = 10;
int blueLed = 9;
int ambientLight; // light value in the room
int power = 150;
float RGB[3];
float CommonMathVariable = 180/PI;

void setup() {
  // put your setup code here, to run once:

  // tells the UNO R3 to send data out to the LEDs
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  // sets all the outputs to LOW (off)
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  digitalWrite(blueLed, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(float x = 0; x < PI; x = x + -.00001) {

    // red LED
    RGB[0] = power * abs(sin(x * (CommonMathVariable)));

    // green LED
    RGB[1] = power * abs(sin((x + PI/3) * (CommonMathVariable)));

    // blue LED
    RGB[2] = power * abs(sin((x + (2 * PI) / 3) * (CommonMathVariable)));

    ambientLight = analogRead(ldrPin);

    if(ambientLight > 600) {
      analogWrite(redLed, RGB[0]);
      analogWrite(greenLed, RGB[1]);
      analogWrite(blueLed, RGB[2]);
    }
    else {
      digitalWrite(redLed, LOW);
      digitalWrite(greenLed, LOW);
      digitalWrite(blueLed, LOW);
    } 

    // Calculate the delay for each color depending on color
    // brightness; brighter LEDs will change colour slower
    for(int i = 0; i < 3; i++) {
      if(RGB[i] < 1) {
        delay(20 * pulseSpeed);
      }
      else if (RGB[i] < 5) {
        delay(10 * pulseSpeed);
      }
      else if (RGB[i] < 10) {
        delay(2 * pulseSpeed);
      }
      else if (RGB[i] < 100) {
        delay(1 * pulseSpeed);
      }
      else {}
    }
    
    delay(1);
  }
}
