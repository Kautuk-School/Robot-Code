void readMotorDriver() {
  analogWrite(-255, 255);   //ENA   pin
  analogWrite(-255, 255);  //ENB pin

  analogWrite(motor1pin1, 200);
  analogWrite(motor1pin2, 0);

  analogWrite(motor2pin1, 200);
  analogWrite(motor2pin2, 0);
  delay(1000);

  analogWrite(motor1pin1, 0);
  analogWrite(motor1pin2, 200);

  analogWrite(motor2pin1, 0);
  analogWrite(motor2pin2, 200);
  delay(1000);
}