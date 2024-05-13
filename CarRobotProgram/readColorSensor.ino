// Initialize the TCS3200 color sensor with specified pins
tcs3200 tcs(COLOR_0, COLOR_1, COLOR_2, COLOR_3, COLOR_OUT);

// Function to read color sensor values
void readColorSensor() {
  const int samples = 5;                                     // Number of samples to average
  long sumRed = 0, sumGreen = 0, sumBlue = 0, sumWhite = 0;  // Variables to store sum of readings

  // Loop for taking multiple samples and summing up the readings
  for (int i = 0; i < samples; i++) {
    sumRed += tcs.colorRead('r');    // Read red component
    sumGreen += tcs.colorRead('g');  // Read green component
    sumBlue += tcs.colorRead('b');   // Read blue component
    sumWhite += tcs.colorRead('c');  // Read clear (white) component
  }

  // Calculate average readings
  int avgRed = sumRed / samples;
  int avgGreen = sumGreen / samples;
  int avgBlue = sumBlue / samples;
  int avgWhite = sumWhite / samples;

  // Print average color sensor readings
  Serial.print("Average Color Sensor Readings: ");
  Serial.print(" R= ");
  Serial.print(avgRed);
  Serial.print(" G= ");
  Serial.print(avgGreen);
  Serial.print(" B= ");
  Serial.print(avgBlue);
  Serial.print(" W(clear)= ");
  Serial.println(avgWhite);
}
