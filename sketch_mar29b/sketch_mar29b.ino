#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> 
#endif

#define NEO_PIN   6 
#define NUMPIXELS 80


Adafruit_NeoPixel pixels(NUMPIXELS, NEO_PIN, NEO_GRB + NEO_KHZ800);


// tl start, tl numleds, bl first, bl last, b first, b last, br first, br last, tr first, tr last, t first, t last, m first, m last

int ledInfo[3][14] {
  {13, 10, 23, 10, 33, 14, 47, 10, 57, 10, 67, 13, 0, 13},

  {0, 10, 10, 10, 20, 13, 33, 11, 44, 13, 54, 13, 67, 13},
  {0, 10, 10, 10, 20, 13, 33, 11, 44, 13, 54, 12, 66, 13}
};

// top left, bot left, bot, bot right, top right, top, mid
int charChart[10][7] = {
  {1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 1, 1, 0, 0},
  {0, 1, 1, 0, 1, 1, 1},
  {0, 0, 1, 1, 1, 1, 1},
  {1, 0, 0, 1, 1, 0, 1},
  {1, 0, 1, 1, 0, 1, 1},
  {1, 1, 1, 1, 0, 1, 1},
  {0, 0, 0, 1, 1, 1, 0},
  {1, 1, 1, 1, 1, 1, 1},
  {1, 0, 0, 1, 1, 1, 1}
};

// Define pin for the button
const int BTN_PIN = 13; // Change this to your button pin number

// Define variables to track button press states
bool shortPress = false;
bool longPress = false;
bool validPress = false;

// Define variables to track button press timing
unsigned long pressStartTime = 0;
unsigned long pressDuration = 0;

// Define constants for press durations
const unsigned long SHORT_PRESS_DURATION = 450; // 1 second for short press
const unsigned long LONG_PRESS_DURATION = 4000;  // 2 seconds for long press

int displayNum = 4;
int signNum =  1;
int displayColor[3] = {0, 0, 210};
int ledBrightness = 210;

void incNum() {
  if (displayNum == 9) {
    displayNum = 0;
  } else {
    displayNum++;
  }
}

void incColor() {
  if ((displayColor[0] == 0) && (displayColor[1] == 0) && (displayColor[2] != 0)) {
    // is blue, set to red
    displayColor[0] = ledBrightness;
    displayColor[1] = 0;
    displayColor[2] = 0;
  } else if ((displayColor[0] != 0) && (displayColor[1] == 0) && (displayColor[2] == 0)) {
    // is red, set to yellow
    displayColor[0] = ledBrightness;
    displayColor[1] = ledBrightness;
    displayColor[2] = 0;
  } else if ((displayColor[0] != 0) && (displayColor[1] != 0) && (displayColor[2] == 0)) {
    // is yellow, set to green
    displayColor[0] = 0;
    displayColor[1] = ledBrightness;
    displayColor[2] = 0;
  } else if ((displayColor[0] == 0) && (displayColor[1] != 0) && (displayColor[2] == 0)) {
    // is green, set to black
    displayColor[0] = 0;
    displayColor[1] = 0;
    displayColor[2] = 0;
  } else if ((displayColor[0] == 0) && (displayColor[1] == 0) && (displayColor[2] == 0)) {
    // is black, set to blue
    displayColor[0] = 0;
    displayColor[1] = 0;
    displayColor[2] = ledBrightness;
  }

}

void setSeg (int numLeds, int startSeg, int r, int g, int b) {
  for (int i = startSeg; i <= (startSeg+numLeds); i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  
  pixels.show();
}

void setup() {
  pinMode(BTN_PIN, INPUT);
  Serial.begin(9600);
  pixels.begin(); 
}

void loop() {
  // Read the state of the button
  bool buttonState = digitalRead(BTN_PIN);

  // Check if the button is pressed
  if (buttonState == HIGH) {
    // Record the time when the button is pressed
    if (pressStartTime == 0) {
      pressStartTime = millis();
    }
  } else {
    // Button released
    if (pressStartTime != 0) {
      // Calculate press duration
      pressDuration = millis() - pressStartTime;
      
      // Determine if it's a short press or a long press
      if (pressDuration < SHORT_PRESS_DURATION) {
        shortPress = true;
      } else if (pressDuration >= SHORT_PRESS_DURATION && pressDuration < LONG_PRESS_DURATION) {
        longPress = true;
      }
      
      // A press is finished, set validPress to true
      validPress = true;
      
      // Reset pressStartTime and pressDuration for next press
      pressStartTime = 0;
      pressDuration = 0;
    }
  }
  
  if (validPress) {
    if (shortPress) {
      incNum();
    } else if (longPress) {
      incColor();
    }
    
    for (int seg = 0; seg < 7; seg++) {
      if (charChart[displayNum][seg] == 1) {
        setSeg(ledInfo[signNum][((seg+1)*2)-1], ledInfo[signNum][((seg+1)*2)-2], displayColor[0], displayColor[1], displayColor[2]);  
      } else {
        setSeg(ledInfo[signNum][((seg+1)*2)-1], ledInfo[signNum][((seg+1)*2)-2], 0, 0, 0);
      }
    }



    // Reset press states
    shortPress = false;
    longPress = false;
    validPress = false;
  }
  
  // Add some delay to avoid continuous reading of the button
  delay(100);
}