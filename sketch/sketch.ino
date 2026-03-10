// Example based on the Object Detection demo by Arduino INC
// Created by Julián Caro Linares for Arduino INC jcarolinares@gmail.com
// CC-BY-SA

#include <Arduino_Modulino.h>
#include <Arduino_RouterBridge.h>


// Create a ModulinoMovement object
ModulinoMovement movement;
ModulinoPixels leds;
int brightness = 25;
float x_accel, y_accel, z_accel; // Accelerometer values in g

ModulinoBuzzer buzzer;
int frequency = 440;  // Frequency of the tone in Hz
int duration = 1000;  // Duration of the tone in milliseconds

unsigned long previousMillis = 0; // Stores last time values were updated
const long interval = 250; // Interval at which to read (16ms) - sampling rate of 62.5Hz and should be adjusted based on model definition
int has_movement = 0; // Flag to indicate if movement data is available

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);
  Bridge.begin();
  Bridge.provide("set_cell_phone", set_cell_phone);
  Bridge.provide("set_bottle", set_bottle);
  Bridge.provide("set_peace", set_peace);

  // Initialize Modulino I2C communication
  Modulino.begin(Wire1);
  leds.begin();

  buzzer.begin();

  // Detect and connect to movement sensor module
  while (!movement.begin()) {
    delay(1000);
  }

  // Set all LEDs to blue
  for (int i = 0; i < 8; i++) {
      leds.set(i, BLUE, 0);
      leds.show();
  }
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  if (currentMillis - previousMillis >= interval) {
    // Save the last time you updated the values
    previousMillis = currentMillis;

    // Read new movement data from the sensor
    has_movement = movement.update();
    if(has_movement == 1) {
      // Get acceleration values
      x_accel = movement.getX();
      y_accel = movement.getY();
      z_accel = movement.getZ();  
    }
  
  }
}

void set_cell_phone(bool state) {
    // LOW state means LED is ON
    digitalWrite(LED_BUILTIN, LOW);
  
    // Set all LEDs to green
    for (int i = 0; i < 8; i++) {
        leds.set(i, GREEN, brightness);
        leds.show();
    }
    buzzer.tone(frequency, duration);  // Generate the tone
    delay(3000);
    buzzer.tone(0, duration);  // Stop the tone
    for (int i = 0; i < 8; i++) {
        leds.set(i, GREEN, 0);
        leds.show();
    }
  digitalWrite(LED_BUILTIN, HIGH);
}

void set_bottle(bool state) {
    // LOW state means LED is ON
    digitalWrite(LED_BUILTIN, LOW);
  
    // Set all LEDs to red
    for (int i = 0; i < 8; i++) {
        leds.set(i, RED, brightness);
        leds.show();
    }
    buzzer.tone(frequency, duration);  // Generate the tone
    delay(3000);
    buzzer.tone(0, duration);  // Stop the tone
    for (int i = 0; i < 8; i++) {
        leds.set(i, RED, 0);
        leds.show();
    }
  digitalWrite(LED_BUILTIN, HIGH);
}

void set_peace(bool state) {
    // LOW state means LED is ON
    digitalWrite(LED_BUILTIN, LOW);
  
    // Set all LEDs to white
    for (int i = 0; i < 8; i++) {
        leds.set(i, WHITE, brightness);
        leds.show();
    }
    buzzer.tone(frequency, duration);  // Generate the tone
    delay(3000);
    buzzer.tone(0, duration);  // Stop the tone
    for (int i = 0; i < 8; i++) {
        leds.set(i, WHITE, 0);
        leds.show();
    }
  digitalWrite(LED_BUILTIN, HIGH);
}






