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

  // Define variables to store previous LED state
  int prevRed = 0;
  int prevGreen = 0;
  int prevBlue = 0;
  
  /*
  if (avgRed > 20 && avgGreen > 15) {
    // Update only if the color is different from the previous one
    if (prevRed != 0 || prevGreen != 255 || prevBlue != 255) {
      prevRed = 0;
      prevGreen = 255;
      prevBlue = 255;
      WiFiDrv::analogWrite(27, prevRed);
      WiFiDrv::analogWrite(25, prevGreen);
      WiFiDrv::analogWrite(26, prevBlue);
    }
  } else if (avgRed > 15) {
    if (prevRed != 255 || prevGreen != 0 || prevBlue != 0) {
      prevRed = 255;
      prevGreen = 0;
      prevBlue = 0;
      WiFiDrv::analogWrite(26, prevRed);
      WiFiDrv::analogWrite(25, prevGreen);
      WiFiDrv::analogWrite(27, prevBlue);
    }
  } else if (avgGreen > 15) {
    if (prevRed != 0 || prevGreen != 255 || prevBlue != 0) {
      prevRed = 0;
      prevGreen = 255;
      prevBlue = 0;
      WiFiDrv::analogWrite(25, prevGreen);
      WiFiDrv::analogWrite(26, prevBlue);
      WiFiDrv::analogWrite(27, prevRed);
    }
  } else if (avgBlue > 15) {
    if (prevRed != 0 || prevGreen != 0 || prevBlue != 255) {
      prevRed = 0;
      prevGreen = 0;
      prevBlue = 255;
      WiFiDrv::analogWrite(27, prevBlue);
      WiFiDrv::analogWrite(26, prevGreen);
      WiFiDrv::analogWrite(25, prevRed);
    }
  }
  */

  
  
  
  
  
  
  
  
  if (((29 < avgRed) && (avgRed < 37)) && ((46 < avgGreen) && (avgGreen < 54)) && ((34 < avgBlue) && (avgBlue < 42))) //Green
  {
    if (prevRed != 0 || prevGreen != 255 || prevBlue != 0) {
      prevRed = 0;
      prevGreen = 255;
      prevBlue = 0;
      WiFiDrv::analogWrite(25, prevGreen);
      WiFiDrv::analogWrite(26, prevBlue);
      WiFiDrv::analogWrite(27, prevRed);
      Serial.println("GREEN RN");
    }
  }
  else if (79 < avgRed < 87 && 53 < avgGreen < 61 && 29 < avgBlue < 37) //yellow
  {
    if (prevRed != 0 || prevGreen != 255 || prevBlue != 255) {
      prevRed = 0;
      prevGreen = 255;
      prevBlue = 255;
      WiFiDrv::analogWrite(27, prevRed);
      WiFiDrv::analogWrite(25, prevGreen);
      WiFiDrv::analogWrite(26, prevBlue);
      Serial.println("Yellow RN");
    }
  }
  else if (11 < avgRed < 19 && 19 < avgGreen < 27 && 46 < avgBlue < 54) //blue
  {
    if (prevRed != 0 || prevGreen != 0 || prevBlue != 255) {
      prevRed = 0;
      prevGreen = 0;
      prevBlue = 255;
      WiFiDrv::analogWrite(27, prevBlue);
      WiFiDrv::analogWrite(26, prevGreen);
      WiFiDrv::analogWrite(25, prevRed);
    }
  } 
  else if (56 < avgRed < 64 && 11 < avgGreen < 19 && 18 < avgBlue < 26) //red
  {
    if (prevRed != 255 || prevGreen != 0 || prevBlue != 0) {
      prevRed = 255;
      prevGreen = 0;
      prevBlue = 0;
      WiFiDrv::analogWrite(26, prevRed);
      WiFiDrv::analogWrite(25, prevGreen);
      WiFiDrv::analogWrite(27, prevBlue);
    }
  } 
}
