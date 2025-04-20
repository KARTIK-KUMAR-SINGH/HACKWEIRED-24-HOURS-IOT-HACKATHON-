// Define the pin numbers
const int inputPin = 2;    // Input pin (e.g., from a sensor or switch)
const int buzzerPin = 8;   // Buzzer pin

void setup() {
  pinMode(inputPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
}

void loop() {
  int inputState = digitalRead(inputPin); // Read input pin

  if (inputState == HIGH) {
    digitalWrite(buzzerPin, HIGH); // Turn on buzzer
  } else {
    digitalWrite(buzzerPin, LOW);  // Turn off buzzer
  }
}