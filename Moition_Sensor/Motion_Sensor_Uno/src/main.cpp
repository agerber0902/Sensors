#include <Arduino.h>
#include <cstdio>

// define pins
#define PIR_SENSOR_IN 5 // Digital input
// #define MOTION_DETECTION_LED
#define ULTRA_SONIC_ECHO 2    // Digital Input for echo value
#define ULTRA_SONIC_TRIGGER 3 // Digital Output to trigger ultra sonic read

// CONSTANTS

// Define variables
int state = LOW;
long ultra_sonic_duration; // Duration of the sound wave
float distance, distance1, diff;

// Define Functions
void readPir();
void readUltraSonicSensor();

void setup()
{
  // Set up Serial
  Serial.begin(9600);
  delay(1000);

  Serial.println("Beginning Setup for UNO R4 PIR and Ultra Sonic Motion Sensor...");

  // Setup pin mode

  // Inputs
  pinMode(PIR_SENSOR_IN, INPUT);
  pinMode(ULTRA_SONIC_ECHO, INPUT);

  // Outputs
  pinMode(ULTRA_SONIC_TRIGGER, OUTPUT);

  // --------

  Serial.println("Setup Complete.");
  delay(1000);
}

void loop()
{
  readUltraSonicSensor();

  delay(5000);
}

void readUltraSonicSensor()
{
  Serial.println("Reading Ultra Sonic Sensor values...");

  digitalWrite(ULTRA_SONIC_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRA_SONIC_TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRA_SONIC_TRIGGER, LOW);

  ultra_sonic_duration = pulseIn(ULTRA_SONIC_ECHO, HIGH, 30000L); // wait up to 30ms
  distance = ultra_sonic_duration * 0.034 / 2;

  Serial.println(ultra_sonic_duration);
  Serial.print("Distance (cm): ");
  Serial.println(distance);

  delay(1000);

}

void readPir()
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
}