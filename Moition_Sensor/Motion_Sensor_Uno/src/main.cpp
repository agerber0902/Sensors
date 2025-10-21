#include <Arduino.h>

// define pins
#define PIR_SENSOR_IN 5 // Digital input
// #define MOTION_DETECTION_LED

// CONSTANTS

// Default values
int state = LOW;

void setup()
{
  // Set up Serial
  Serial.begin(9600);
  delay(1000);

  Serial.println("Beginning Setup for UNO R4 PIR Motion Sensor...");

  // Setup pin mode
  pinMode(PIR_SENSOR_IN, INPUT);

  Serial.println("Setup Complete.");
  delay(1000);
}

void loop()
{
  Serial.println("Reading PIR Sensor values...");

  // Read pir value
  int pir_value = digitalRead(PIR_SENSOR_IN);
  Serial.println(pir_value);

  if (pir_value == HIGH)
  {
    // digitalWrite(led, HIGH);
    Serial.println("Alert");
    delay(500); // Delay of led is 500
    if (state == LOW)
    {
      Serial.println(" Motion detected");
      state = HIGH;
    }
  }
  else
  {
    // digitalWrite(led, LOW);
    Serial.println("Non Alert");
    delay(500);
    if (state == HIGH)
    {
      Serial.println("The action/ motion has stopped");
      state = LOW;
    }
  }

  delay(5000);
}
