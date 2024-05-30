#include <tcs3200.h>
#include <WiFiNINA.h>

#define IR_1 4
#define IR_2 7
#define IR_3 8
#define IR_4 12

#define COLOR_0 A0
#define COLOR_1 A1
#define COLOR_2 A2
#define COLOR_3 A3
#define COLOR_OUT A4

#define TRIG_PIN 10
#define ECHO_PIN 11

#define MOTOR_PIN1 3
#define MOTOR_PIN2 5
#define MOTOR_PIN3 6
#define MOTOR_PIN4 9

#define LED_R 25
#define LED_G 26
#define LED_B 27

String currentState = "Null";
String oldCurrentState = "Null";

unsigned long irSensorMillis = 0;
unsigned long colorSensorMillis = 0;
unsigned long ultrasonicSensorMillis = 0;
unsigned long motorlogicMillis = 0;

String turnDirection = "";
String lastTurnDirection = "";
bool isTurning = false;
bool wallDetected = false;

int currentDistance = 1000;

unsigned long currentMillis;

void setup() {
  Serial.begin(250000);

  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(IR_3, INPUT);
  pinMode(IR_4, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(MOTOR_PIN3, OUTPUT);
  pinMode(MOTOR_PIN4, OUTPUT);

  WiFiDrv::pinMode(LED_R, OUTPUT);
  WiFiDrv::pinMode(LED_G, OUTPUT);
  WiFiDrv::pinMode(LED_B, OUTPUT);

  
}

// the loop function runs over and over again forever
void loop() {
  currentMillis = millis();
  Serial.println(currentMillis);
  
  if (currentMillis - colorSensorMillis >= 20) {
    colorSensorMillis = currentMillis;
    readColorSensor();
  }

  if (currentMillis - ultrasonicSensorMillis >= 20) {
    ultrasonicSensorMillis = currentMillis;
    readUltrasonic();
  }

  robotLogic();
}
