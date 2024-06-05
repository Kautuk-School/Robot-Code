#include <tcs3200.h>  // Include library for TCS3200 color sensor
#include <WiFiNINA.h> // Include library for WiFi module

// Define pin numbers for IR sensors
#define IR_1 4
#define IR_2 7
#define IR_3 8
#define IR_4 12

// Define pin numbers for TCS3200 color sensor
#define COLOR_0 A0
#define COLOR_1 A1
#define COLOR_2 A2
#define COLOR_3 A3
#define COLOR_OUT A4

// Define pin numbers for ultrasonic sensor (HC-SR04)
#define TRIG_PIN 10
#define ECHO_PIN 11

// Define pin numbers for motor control
#define MOTOR_PIN1 3
#define MOTOR_PIN2 5
#define MOTOR_PIN3 6
#define MOTOR_PIN4 9

// Define pin numbers for RGB LEDs
#define LED_R 25
#define LED_G 26
#define LED_B 27

// Define variables to store current and old states
String currentState = "Null";
String oldCurrentState = "Null";

// Define variables to track millis for sensor readings and motor logic
unsigned long irSensorMillis = 0;
unsigned long colorSensorMillis = 0;
unsigned long ultrasonicSensorMillis = 0;
unsigned long motorlogicMillis = 0;

// Define variables for motor control and direction
String turnDirection = "";
String lastTurnDirection = "";
bool isTurning = false;
bool wallDetected = false;

// Define variable to store current distance measured by ultrasonic sensor
int currentDistance = 1000;

unsigned long currentMillis; // Variable to store current time

void setup() {
  Serial.begin(250000); // Start serial communication

  // Set pin modes for IR sensors
  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(IR_3, INPUT);
  pinMode(IR_4, INPUT);

  // Set pin modes for ultrasonic sensor
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Set pin modes for motor control
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);

  // Set pin modes for RGB LEDs
  WiFiDrv::pinMode(LED_R, OUTPUT);
  WiFiDrv::pinMode(LED_G, OUTPUT);
  WiFiDrv::pinMode(LED_B, OUTPUT);

  
}

// Main loop function
void loop() {
  currentMillis = millis(); // Get current time in milliseconds
  Serial.println(currentMillis); // Print current time
  
  // Read color sensor data if enough time has passed
  if (currentMillis - colorSensorMillis >= 20) {
    colorSensorMillis = currentMillis;
    readColorSensor();
  }

  // Read ultrasonic sensor data if enough time has passed
  if (currentMillis - ultrasonicSensorMillis >= 20) {
    ultrasonicSensorMillis = currentMillis;
    readUltrasonic();
  }

  // Perform robot logic based on sensor readings
  robotLogic();
}
