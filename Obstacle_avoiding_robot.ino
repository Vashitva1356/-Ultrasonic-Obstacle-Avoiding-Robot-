/*
  Ultrasonic Obstacle Avoiding Robot
  Arduino UNO + L298N Motor Driver + Servo + HC-SR04
  Robot scans left and right to find safest path
*/

#include <Servo.h>

#define TRIG_PIN 9
#define ECHO_PIN 8
#define SERVO_PIN 10
#define IN1 3
#define IN2 4
#define IN3 5
#define IN4 6

Servo myServo;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  myServo.attach(SERVO_PIN);
  myServo.write(90); // Center
  Serial.begin(9600);
}

// Function to get distance in cm
long getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  long duration = pulseIn(ECHO_PIN, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

// Motor control functions
void forward() {
  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW);
}

void stopBot() {
  digitalWrite(IN1,LOW); digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW); digitalWrite(IN4,LOW);
}

void left() {
  digitalWrite(IN1,LOW); digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH); digitalWrite(IN4,LOW);
}

void right() {
  digitalWrite(IN1,HIGH); digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW); digitalWrite(IN4,HIGH);
}

void loop() {
  long d = getDistance();
  
  if(d > 5 && d < 15){ // Obstacle detected
    stopBot();
    delay(300);

    // Scan left
    myServo.write(0);
    delay(500);
    long leftDist = getDistance();

    // Scan right
    myServo.write(180);
    delay(500);
    long rightDist = getDistance();

    // Center servo
    myServo.write(90);
    delay(300);

    // Choose safer path
    if(leftDist > rightDist){
      left();
      delay(600);
    } else {
      right();
      delay(600);
    }
  } else {
    forward();
    delay(200);
  }
}
