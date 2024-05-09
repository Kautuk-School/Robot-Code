#include <tcs3200.h>

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

int motor1pin1 = 3;
int motor1pin2 = 5;
int motor2pin1 = 6;
int motor2pin2 = 9;

unsigned long irSensorMillis = 0;
unsigned long colorSensorMillis = 0;
unsigned long ultrasonicSensorMillis = 0;
unsigned long motorDriverMillis = 0;

void setup() {
  Serial.begin(9600);
  pinMode(IR_1, INPUT);
  pinMode(IR_2, INPUT);
  pinMode(IR_3, INPUT);
  pinMode(IR_4, INPUT);

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - irSensorMillis >= 500) {
    irSensorMillis = currentMillis;
    readInfrared();
  }

  if (currentMillis - colorSensorMillis >= 250) {
    colorSensorMillis = currentMillis;
    readColorSensor();
  }

  if (currentMillis - ultrasonicSensorMillis >= 250) {
    ultrasonicSensorMillis = currentMillis;
    readUltrasonic();
  }

  if (currentMillis - motorDriverMillis >= 250) {
    motorDriverMillis = currentMillis;
    readMotorDriver();
  }
}
