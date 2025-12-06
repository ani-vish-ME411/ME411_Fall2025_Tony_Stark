#include <Servo.h>

// ------------------- SERVO SETUP -------------------
Servo servoUltrasonic;  // Servo on pin 11 (mouth) 
Servo servoPhotocell;   // Servo on pin 8 (eyes)

// ------------------- ULTRASONIC SETUP -------------------
const int trigPin = 9;
const int echoPin = 10;
long duration;
int distance;

const int handThreshold = 5;  // cm — adjust if needed

void setup() {
  Serial.begin(9600);

  servoUltrasonic.attach(11);
  servoPhotocell.attach(8);

  servoUltrasonic.write(0);
  servoPhotocell.write(0);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  Serial.println("System Ready");
}

void loop() {

  // ---------------- READ ULTRASONIC ----------------
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // ---------------- HAND DETECTED ----------------
  if (distance > 0 && distance < handThreshold) {

    // 🔹 This is what your Python script is waiting for:
    Serial.println("PLAY");

    delay(800);

    Serial.println("Hand detected → Waving for 5 seconds.");

    unsigned long startTime = millis();

    // Wave for 10 seconds
    while (millis() - startTime < 4000) {

      // Sweep forward
      for (int angle = 0; angle <= 20; angle += 1) {
        int eyesAngle = angle / 2;    // 0→10 degrees
        servoUltrasonic.write(angle); // mouth: 0→20
        servoPhotocell.write(eyesAngle); // eyes: 0→10
        delay(15);
      }

      // Sweep backward
      for (int angle = 20; angle >= 0; angle -= 1) {
        int eyesAngle = angle / 2;    // 10→0 degrees
        servoUltrasonic.write(angle); // mouth: 20→0
        servoPhotocell.write(eyesAngle); // eyes: 10→0
        delay(15);
      }
    }
  }

  // ---------------- NO HAND ----------------
  else {
    servoUltrasonic.write(0);
    servoPhotocell.write(0);
    Serial.println("No hand → Servos = 0°");
  }

  delay(100);
}
