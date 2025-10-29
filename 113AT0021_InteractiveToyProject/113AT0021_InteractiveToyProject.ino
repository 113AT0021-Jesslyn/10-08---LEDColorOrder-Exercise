// Pin Setup
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;
const int buttonPin = 2;

// Mood Variables
int mood = 10;  // start from neutral
int buttonState = 0;
bool buttonPressed = false;

unsigned long lastPressTime = 0;
unsigned long lastDecreaseTime = 0;

const long unTouchInterval = 5000;  // 5 seconds no touch → start decreasing
const long decreaseInterval = 1000; // decrease 1 point per second

// Function Prototype
void showLEDState(int value);

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  showLEDState(mood);

  buttonState = digitalRead(buttonPin);

  // If button pressed (+1 mood)
  if (buttonState == HIGH && !buttonPressed) {
    mood++;
    if (mood > 20) mood = 20;
    buttonPressed = true;
    lastPressTime = millis(); // reset untouched timer
  }

  // Detect button released
  if (buttonState == LOW && buttonPressed) {
    buttonPressed = false;
  }

  unsigned long currentTime = millis();

  // Check if untouched for 5 seconds
  if (currentTime - lastPressTime > unTouchInterval) {
    // Reduce 1 point per second
    if (currentTime - lastDecreaseTime > decreaseInterval) {
      mood--;
      if (mood < 0) mood = 0;
      lastDecreaseTime = currentTime;
    }
  }
}

// Mood-to-RGB Gradient: Red → Green → Blue
void showLEDState(int value) {
  if (value < 0) value = 0;
  if (value > 20) value = 20;

  float t = value / 20.0;  // convert 0..20 to 0.0..1.0
  int r, g, b;

  if (t <= 0.5) {
    // Red → Green (0 to 10 points)
    float x = t / 0.5;
    r = (int)((1.0 - x) * 255); // 255 → 0
    g = (int)(x * 255);         // 0 → 255
    b = 0;
  } else {
    // Green → Blue (10 to 20 points)
    float x = (t - 0.5) / 0.5;
    r = 0;
    g = (int)((1.0 - x) * 255); // 255 → 0
    b = (int)(x * 255);         // 0 → 255
  }

  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
}
