void readMotorDriver(int speed1, int speed2) {
  float motor1Multiplier = 1.0;
  float motor2Multiplier = 0.95;

  int adjustedSpeed1 = speed1 * motor1Multiplier;
  int adjustedSpeed2 = speed2 * motor2Multiplier;

  adjustedSpeed1 = max(-255, min(255, adjustedSpeed1));
  adjustedSpeed2 = max(-255, min(255, adjustedSpeed2));

  analogWrite(MOTOR_PIN1, adjustedSpeed1 > 0 ? adjustedSpeed1 : 0);
  analogWrite(MOTOR_PIN2, adjustedSpeed1 < 0 ? -adjustedSpeed1 : 0);
  analogWrite(MOTOR_PIN3, adjustedSpeed1 > 0 ? adjustedSpeed2 : 0);
  analogWrite(MOTOR_PIN4, adjustedSpeed1 < 0 ? -adjustedSpeed2 : 0);
}
