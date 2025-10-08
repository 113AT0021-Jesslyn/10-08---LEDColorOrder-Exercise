const int buttonPin = 2;
const int rLEDPin = 3;
const int gLEDPin = 4; 
const int bLEDPin = 5;

int buttonState = 0;
int ledColor = 0;
bool ButtonPressed = false;
bool ledColorOrder = true;
const long interval = 1000;
unsigned long previousMillis = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode (rLEDPin, OUTPUT);
  pinMode (gLEDPin, OUTPUT);
  pinMode (bLEDPin, OUTPUT);
  pinMode (buttonPin, INPUT);
  Serial.begin(9600);
}

void loop() {

  buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH && !ButtonPressed) {
    ledColorOrder = !ledColorOrder;
    ButtonPressed = true;
  // delay(100);
  } 

  if (buttonState == LOW && ButtonPressed) {
    ButtonPressed = false;
  }

  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;
    if(ledColorOrder == true){
      ledColor = ledColor + 1;
      if(ledColor > 3)
        ledColor = 0;
    }
    else{
      ledColor = ledColor - 1;
      if(ledColor < 0)
        ledColor = 3;
    }
  }

  if (ledColor == 0) {
    // currentcolor = "Red";
    digitalWrite(rLEDPin, LOW);
    digitalWrite(gLEDPin, HIGH);
    digitalWrite(bLEDPin, HIGH);
  }

  else if (ledColor == 1) {
    // currentcolor = "Green";
    digitalWrite(rLEDPin, HIGH);
    digitalWrite(gLEDPin, LOW);
    digitalWrite(bLEDPin, HIGH);
  }

  else if (ledColor == 2) {
    // currentcolor = "Blue";
    digitalWrite(rLEDPin, HIGH);
    digitalWrite(gLEDPin, HIGH);
    digitalWrite(bLEDPin, LOW);
  }

  else if (ledColor == 3) {
    // currentcolor = "White";
    digitalWrite(rLEDPin, LOW);
    digitalWrite(gLEDPin, LOW);
    digitalWrite(bLEDPin, LOW);
  }

  else if(ledColor == 4) {
    ledColor = 0;
  }


}
