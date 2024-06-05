// Variables to control initial forward motion and duration
bool initialForwardMotion = false;
const unsigned long initialMotionDuration = 275;

// Variables to control turning
unsigned long turnStartTime = 0;
const unsigned long initialTurnDuration = 600;
int turnSpeed = 150; // Speed of turning

// Modifiers for adjusting turning speed
int leftTurnModifier = 40;
int rightTurnModifier = 25;

// Threshold for checking sensor readings
const unsigned long sensorCheckThreshold = 50;

// Variables to store time of first detection for each sensor
unsigned long firstDetectionTime1 = 0;
unsigned long firstDetectionTime4 = 0;

// Main function for robot logic
void robotLogic() {
  turnLogic();   // Execute turn logic
  motorLogic();  // Execute motor logic (IR Sensor Detection Function)
}

// Function for turn logic
void turnLogic() {
  int* IRvalues;
  IRvalues = readInfrared();  // Read infrared sensor values
  
  // Check if a wall has been detected
  if (currentDistance < 8 && wallDetected == false) {
    isTurning = true;
    wallDetected = true;
    turnStartTime = currentMillis;
    initialForwardMotion = true;
  }
  
  // If the robot is not turning and a wall is not detected
  if (!isTurning && wallDetected == false) {
    // Check outer sensors for line detection and start the threshold timer
    if (IRvalues[3] == 1 && firstDetectionTime1 == 0) {
      firstDetectionTime1 = currentMillis;
      Serial.println("Detected Left Sensor");
    }
    if (IRvalues[0] == 1 && firstDetectionTime4 == 0) {
      firstDetectionTime4 = currentMillis;
      Serial.println("Detected Right Sensor");
    }
    
    // Check if both sensors detect a line within the threshold and determine the turn direction
    if (firstDetectionTime1 > 0 && currentMillis - firstDetectionTime1 < sensorCheckThreshold && firstDetectionTime4 > 0 && currentMillis - firstDetectionTime4 < sensorCheckThreshold) {
      isTurning = true;
      initialForwardMotion = true;
      turnStartTime = currentMillis;
      turnDirection = lastTurnDirection;
      firstDetectionTime1 = 0;
      firstDetectionTime4 = 0;
      lastTurnDirection = turnDirection;
      Serial.print("Solid Line Detected (Sensors 1 and 4) - turning ");
      Serial.println(turnDirection);
    } else if (firstDetectionTime1 > 0 && currentMillis - firstDetectionTime1 >= sensorCheckThreshold) {
      isTurning = true;
      initialForwardMotion = true;
      turnStartTime = currentMillis;
      turnDirection = "left";
      firstDetectionTime1 = 0;
      lastTurnDirection = turnDirection;
      Serial.println("Left Turn Detected");
    } else if (firstDetectionTime4 > 0 && currentMillis - firstDetectionTime4 >= sensorCheckThreshold) {
      isTurning = true;
      initialForwardMotion = true;
      turnStartTime = currentMillis;
      turnDirection = "right";
      firstDetectionTime4 = 0;
      lastTurnDirection = turnDirection;
      Serial.println("Right Turn Detected");
    }
  }
}

// Function for motor logic
void motorLogic() {
  int* IRvalues;
  IRvalues = readInfrared();
  
  // Apply robot logic based on sensor readings and turning flags
  if (!isTurning && !wallDetected) {
    // Move forward if both inner sensors detect a line
    if (IRvalues[1] == 1 && IRvalues[2] == 1) {
      motorControl(220, 220);
      currentState = "Forward";
    } else if (IRvalues[1] == 0 && IRvalues[2] == 1) {
      motorControl(160, 220);
      currentState = "Left";
    } else if (IRvalues[1] == 1 && IRvalues[2] == 0) {
      motorControl(220, 160);
      currentState = "Right";
    } else if (IRvalues[0] == 1 && IRvalues[1] == 1 && IRvalues[2] == 1 && IRvalues[3] == 1) {
      // Continue previous motion direction if all sensors detect a line
      if (currentState == "Forward") {
        motorControl(220, 220);
      } else if (currentState == "Left") {
        motorControl(160, 220);
      } else if (currentState == "Right") {
        motorControl(220, 160);
      }
    }
  } else if (isTurning && !wallDetected) {
    // Handle turning based on direction determined
    if (initialForwardMotion) {
      motorControl(200, 200);  // Continue moving forward for the initial duration
      currentState = "Bumping Out...";
      delay(initialMotionDuration);
      initialForwardMotion = false;
    } else {
      // Continue turning left or right
      if (turnDirection == "left") {
        if (currentMillis - turnStartTime >= initialTurnDuration && IRvalues[2] == 1) {
          isTurning = false;
          motorControl(0, 0);
          currentState = "Turning Left - Next Line Detected";
          motorControl(turnSpeed, -turnSpeed);
          delay(100);
          motorControl(0, 0);
          delay(50);
          currentState = "Forward";
        } else {
          motorControl(-turnSpeed - leftTurnModifier, turnSpeed - rightTurnModifier);
          currentState = "Turning Left - No Line Yet Detected";
        }
      } else if (turnDirection == "right") {
        if (currentMillis - turnStartTime >= initialTurnDuration && IRvalues[1] == 1) {
          isTurning = false;
          motorControl(0, 0);
          currentState = "Turning Right - Next Line Detected";
          motorControl(-turnSpeed, turnSpeed);
          delay(100);
          motorControl(0, 0);
          delay(50);
          currentState = "Forward";
        } else {
          motorControl(turnSpeed + leftTurnModifier, -turnSpeed + rightTurnModifier);
          currentState = "Turning Right - No Line Yet Detected";
        }
      }
    }
  } else if (isTurning && wallDetected) {
    // Handle turning triggered by detecting a wall
    if (initialForwardMotion) {
      motorControl(-200, -200);  // Continue moving forward for the initial duration
      currentState = "Stopping...";
      delay(100);
      initialForwardMotion = false;
    } else {
      // Continue turning left
      if (currentMillis - turnStartTime >= initialTurnDuration && IRvalues[2] == 1) {
        isTurning = false;
        motorControl(0, 0);
        currentState = "Turning Left - Next Line Detected";
        motorControl(turnSpeed, -turnSpeed);
        delay(50);
        motorControl(0, 0);
        delay(50);
        wallDetected = false;
        currentState = "Forward";
      } else {
        motorControl(-turnSpeed - leftTurnModifier, turnSpeed - rightTurnModifier);
        currentState = "Turning Left - No Line Yet Detected";
      }
    }
  }
}
