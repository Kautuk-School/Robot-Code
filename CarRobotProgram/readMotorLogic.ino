void motorLogic() {
  int IRvalues;
  IRvalues = readInfrared();

  if (IRvalues[1] == 1 && IRvalues[2] == 1) {
    motorControl(200, 200);
    currentState = "Forward";
  } else if (IRvalues[1] == 0 && IRvalues[2] == 1) {
    motorControl(150, 200);
    currentState = "Left";
  } else if (IRvalues[1] == 1 && IRvalues[2] == 0) {
    motorControl(200, 150);
    currentState = "Right";
  } else if (IRvalues[1] == 0 && IRvalues[1] == 1 && IRvalues[2] == 1 && IRvalues[3] == 1) {
    if (currentState == "Forward") {
      motorControl(200, 200);
    } else if (currentState == "Left") {
      motorControl(150, 200);
    } else if (currentState == "Right") {
      motorControl(200, 150);
    }
  }
}