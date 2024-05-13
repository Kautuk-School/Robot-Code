#include <tcs3200.h>

// Define pins for infrared sensors
#define IR_1 4
#define IR_2 7
#define IR_3 8
#define IR_4 12

// Define pins for color sensor
#define COLOR_0 A0
#define COLOR_1 A1
#define COLOR_2 A2
#define COLOR_3 A3
#define COLOR_OUT A4

// Define pins for ultrasonic sensor
#define TRIG_PIN 10
#define ECHO_PIN 11

// Define pins for motor driver
#define MOTOR_PIN1 3
#define MOTOR_PIN2 5
#define MOTOR_PIN3 6
#define MOTOR_PIN4 9

// Variables to track time for different sensors and motor control
unsigned long irSensorMillis = 0;
unsigned long colorSensorMillis = 0;
unsigned long ultrasonicSensorMillis = 0;
unsigned long motorDriverMillis = 0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set pins mode for infrared sensors
  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(IR_3, INPUT);
  pinMode(IR_4, INPUT);

  // Set pins mode for ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set pins mode for motor driver
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);
}

// Main loop
void loop() {
  // Get current time
  unsigned long currentMillis = millis();

  // Read infrared sensors every 500 milliseconds
  if (currentMillis - irSensorMillis >= 500) {
    irSensorMillis = currentMillis;
    readInfrared();
  }

  // Read color sensor every 250 milliseconds
  if (currentMillis - colorSensorMillis >= 250) {
    colorSensorMillis = currentMillis;
    readColorSensor();
  }

  // Read ultrasonic sensor every 250 milliseconds
  if (currentMillis - ultrasonicSensorMillis >= 250) {
    ultrasonicSensorMillis = currentMillis;
    readUltrasonic();
  }

  // Perform motor actions
  readMotorDriver(255, 255);  // Move forward
  delay(1000);
  readMotorDriver(0, 0);  // Stop
  delay(100);
  readMotorDriver(255, -255);  // Rotate
  delay(500);
  readMotorDriver(0, 0);  // Stop
  delay(100);
}
