#include <Arduino.h>

// Define Pins
#define MOISTURE_SENSOR A1 // Analog Input for Moisture Sensor
#define MOISTURE_ALERT D10 // Digital Output for Moisture Sensor Alert

// Constants
const float MOISTURE_THROWAWAY_THRESHOLD = 10.0; // threshold for noise values to ignore
const float MOISTURE_ALERT_THRESHOLD = 1000; // threshold for moisture alert

// Function Declarations:
void readMoisture();
void alert(uint8_t alertOutput, float alertThreshold, float ignoreThreshold, float reading);

void setup() {
  // Set Serial Rate
  Serial.begin(115200);
  delay(1000);
  Serial.println("Beginning setup for ESP32 Moisture Sensor..");
  
  // Configure Pin Modes
  pinMode(MOISTURE_SENSOR, INPUT);
  pinMode(MOISTURE_ALERT, OUTPUT);

  // TODO: Set up ESP Now communication

  Serial.println("ESP32 Moisture Sensor setup complete.");
  delay(1000);

}

void loop() {
  
  // Read the moisture value and set alert
  readMoisture();

  delay(5000);
}

// Function Definitions:
// TODO: will more than likely have separate files

// Reads analog input and alerts if inside alert threshold
void readMoisture() {

  Serial.println("Reading Moisture Sensor value..");

  // Read moisture value
  float moistureReading = analogRead(MOISTURE_SENSOR);
  Serial.printf("Moisture Reading from input pin: %f\n", moistureReading);

  // Alert Call
  alert(MOISTURE_ALERT, MOISTURE_ALERT_THRESHOLD, MOISTURE_THROWAWAY_THRESHOLD, moistureReading);
}

// Sets the alert pin input based on threshold input and reading value input
void alert(uint8_t alertOutput, float alertThreshold, float ignoreThreshold, float reading){
  // If the reading is within the alert threshold, set the alert
  bool isAlert = (reading > alertThreshold) && (reading < ignoreThreshold);

  digitalWrite(MOISTURE_ALERT, isAlert);

  Serial.printf("Alert: %s\n", isAlert ? "true" : "false");
}