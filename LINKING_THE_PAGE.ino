#include <WiFi.h>
#include <HTTPClient.h>

#define TRIG_PIN    5
#define ECHO_PIN    18
#define BUZZER_PIN  19

// Replace with your WiFi credentials
const char* ssid     = "PU_Visitors";
const char* password = "Passme@224!";

// Replace with your Google Apps Script Web App URL
const char* GOOGLE_SCRIPT_URL = "";

bool buzzerWasHigh = false;

void setup() {
  Serial.begin(115200);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Connect to Wi-Fi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  long duration;
  float distance;

  // Trigger ultrasonic sensor
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, 30000);
  distance = (duration * 0.0343) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > 4.0) {
    digitalWrite(BUZZER_PIN, HIGH);

    if (!buzzerWasHigh) { // only send once when it turns high
      sendToGoogleSheet(distance);
      buzzerWasHigh = true;
    }

  } else {
    digitalWrite(BUZZER_PIN, LOW);
    buzzerWasHigh = false;
  }

  delay(200);
}

void sendToGoogleSheet(float distance) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(GOOGLE_SCRIPT_URL) + "?distance=" + String(distance);
    
    http.begin(url);
    int httpCode = http.GET(); // send GET request

    if (httpCode > 0) {
      Serial.println("Data sent to Google Sheets!");
    } else {
      Serial.println("Error sending data.");
    }
    http.end();
  } else {
    Serial.println("WiFi not connected!");
  }
}
