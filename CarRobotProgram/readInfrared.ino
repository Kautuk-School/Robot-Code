// Function to read values from infrared sensors
int* readInfrared() {
  static int IRvalues[4];
  // Read values from each infrared sensor
  IRvalues[0] = digitalRead(IR_1);
  IRvalues[1] = digitalRead(IR_2);
  IRvalues[2] = digitalRead(IR_3);
  IRvalues[3] = digitalRead(IR_4);

  // Print the values of each infrared sensor
  Serial.print("IR_1: ");
  Serial.print(IRvalues[0]);
  Serial.print(", IR_2: ");
  Serial.print(IRvalues[1]);
  Serial.print(", IR_3: ");
  Serial.print(IRvalues[2]);
  Serial.print(", IR_4: ");
  Serial.println(IRvalues[3]);

  return IRvalues;
}
