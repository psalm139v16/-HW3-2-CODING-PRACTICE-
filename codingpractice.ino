// ============================================================================
// HW3-2: CODING PRACTICE 
//
// Pin Setup:
// Button Signal -> Pin D2
// RGB LED Color Pin (R/G/B) -> Pin D3
//
// States:
// 0 = Steady ON
// 1 = Slow Blink
// 2 = Medium Blink
// 3 = Fast Blink
//
// Each button press changes the state.
// After State 3, the next press returns to State 0.
// ============================================================================

const int buttonPin = 2;  // Button Signal -> Pin D2
const int ledPin = 3;     // RGB LED Color Pin -> Pin D3

// State Tracking Variables
int state = 0;             // 0: Steady ON, 1: Slow, 2: Medium, 3: Fast
int buttonState = 0;
bool buttonPressed = false;

// Timing Variables
unsigned long previousMillis = 0;
bool ledOn = true;

// Blinking Intervals (in milliseconds)
const int slowInterval = 800;   
const int mediumInterval = 400;  
const int fastInterval = 150;    


void ledWrite(bool turnOn) {
  digitalWrite(ledPin, turnOn ? LOW : HIGH);

  
}

void setup() {
  Serial.begin(9600);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

  ledWrite(true);
}

void loop() {
  checkButton();
  updateLEDBehavior();
}



void checkButton() {
  buttonState = digitalRead(buttonPin);

  // Button pressed down (LOW on INPUT_PULLUP)
  if (buttonState == LOW && !buttonPressed) {
    buttonPressed = true;

    // Cycle through states: 0 -> 1 -> 2 -> 3 -> 0
    state = (state + 1) % 4;

    Serial.print("State Changed to: ");
    Serial.println(state);

    // Reset blink timing when changing states
    previousMillis = millis();
    ledOn = true;
    ledWrite(true);
  }

  // Button released (HIGH)
  if (buttonState == HIGH && buttonPressed) {
    buttonPressed = false;
  }
}


void updateLEDBehavior() {
  unsigned long currentMillis = millis();

  switch (state) {

    case 0:
      // State 0: Steady ON
      ledWrite(true);
      break;

    case 1:
      // State 1: Slow Blink
      if (currentMillis - previousMillis >= slowInterval) {
        previousMillis = currentMillis;
        ledOn = !ledOn;
        ledWrite(ledOn);
      }
      break;

    case 2:
      // State 2: Medium Blink
      if (currentMillis - previousMillis >= mediumInterval) {
        previousMillis = currentMillis;
        ledOn = !ledOn;
        ledWrite(ledOn);
      }
      break;

    case 3:
      // State 3: Fast Blink
      if (currentMillis - previousMillis >= fastInterval) {
        previousMillis = currentMillis;
        ledOn = !ledOn;
        ledWrite(ledOn);
      }
      break;
  }
}