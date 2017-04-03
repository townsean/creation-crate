#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 6, NEO_GRB + NEO_KHZ800);

int initX, initY, goalIndex, cursorIndex;
unsigned long goalStartTime; // used to figure out how long the cursor has been at the goal
#define bucket 25 // range in accelerometer that coorelates to each coordinate value

void setup() {
  // put your setup code here, to run once:
  strip.begin();
  strip.show(); // start up the LED panel

  analogReference(EXTERNAL); // uses 3.3 volts as the maximum analog reading value
  pinMode(A0, INPUT); // X axis
  pinMode(A1, INPUT); // y axis
  pinMode(A2, INPUT); // used to pick random number

  initX = analogRead(A0); // initial reading (while breadboard is flat)
  initY = analogRead(A1);

  randomSeed(analogRead(A2)); // Pick a seed for the random number generator
  goalIndex = random(15); // Randomly pick a starting place
  goalStartTime = millis(); // Sets the elaped time in the goal to 0
}

// Maps the "snaking" LED matrix to the coordinate array
void setNthPixel(int pixel, uint32_t color) {
  if(pixel <= 3) {
    strip.setPixelColor(pixel, color);
  } else if (pixel <= 7) {
    strip.setPixelColor(11 - pixel, color); // flips LEDs 4, 5, 6, 7 to be 7, 6, 5, 4
  } else if (pixel <= 11) {
    strip.setPixelColor(pixel, color);  
  } else if (pixel <= 15) {
    strip.setPixelColor(27 - pixel, color); // flips LEDs 12, 13, 14, 15 to be 16, 14, 13, 12  
  }
}

int getCursorIndex() {
  int x, y, xOffset, yOffset;

  xOffset = initX - 2 * bucket;
  yOffset = initY - 2 * bucket;

  x = (analogRead(A0) - xOffset) / bucket;
  y = (analogRead(A1) - yOffset) / bucket;

  if(x < 0 || x > 3 || y < 0 || y > 3) {
    // if the coordinate is off the LED matrix, we'll set the value to -1
    return -1;  
  } else {
    // converts the x, y coordinates into one number that correlates to the LED matrix
    return x*4+y;  
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  cursorIndex = getCursorIndex();

  for(int i = 0; i < 16; i++) {
    // clears the led panel
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }

  // show the goal LED
  setNthPixel(goalIndex, strip.Color(0,0, 20)); 

  if(cursorIndex != -1) {
    // show the cursor LED
    setNthPixel(cursorIndex, strip.Color(0, 20, 0));
  }

  if(cursorIndex == goalIndex ) {
    // if the goal and cursor line up, show a combined color
    setNthPixel(cursorIndex, strip.Color(0, 10, 10));    
  } else{    
    goalStartTime = millis(); // reset the elapsed time  
  }

  if(millis() - goalStartTime >= 1500) {
    // if the goal has been selected for 1.5 seconds
    goalIndex = random(15); // select a new goal
    goalStartTime = millis(); // reset the elapsed time
  }

  strip.show();
}
