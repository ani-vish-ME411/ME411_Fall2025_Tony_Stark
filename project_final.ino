// Includes the Arduino Stepper Library
#include <Stepper.h>

// Steps per full revolution for 28BYJ-48
const int stepsPerRevolution = 2048;

// 90 degrees = 512 steps
const int stepsFor90Deg = stepsPerRevolution / 4;

// Capacitive touch sensor pin
const int touchPin = 2;

// LED pins (4 white + 4 blue)
int ledPins[8] = {3,4,5,6,7,12,13,A0};

// Create stepper instance (IN1, IN3, IN2, IN4)
Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

// State variable to prevent repeated triggers
bool actionInProgress = false;

void setup() {
  Serial.begin(9600);     
  pinMode(touchPin, INPUT);

  // Set LED pins as output
  for (int i = 0; i < 8; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW); // Make sure all LEDs start OFF
  }

  myStepper.setSpeed(10); 
}

void loop() {

  int touchState = digitalRead(touchPin);

  // Trigger only once per touch
  if (touchState == HIGH && !actionInProgress) {
    actionInProgress = true;
     // Notify laptop to play audio
    Serial.println("PLAY_AUDIO");

    // Turn on LEDs one by one (0.5 sec delay)
    for (int i = 0; i < 8; i++) {
      digitalWrite(ledPins[i], HIGH);
      delay(500);
    }


   

    // Move 0° → 90°
    myStepper.step(-stepsFor90Deg);


    // Wait 10 seconds
    delay(10000);

    // Move back 90° → 0°
    myStepper.step(stepsFor90Deg);

    // Turn off ALL LEDs after motor completes
    for (int i = 0; i < 8; i++) {
      digitalWrite(ledPins[i], LOW);
    }

    // Require touch to be released before next trigger
    while (digitalRead(touchPin) == HIGH) {
      delay(10);
    }

    actionInProgress = false;
  }
}
