/**
 * Create an extinguishing arm
 * @param armMotorPin the signal pin of the arm servo 
 * @param flameSensorPin the analog input pin of the flame sensor
 */
ExtinguishingArm::ExtinguishingArm(pin armMotorPin, pin flameSensorPin) :
  armMotor(),
  flameSensor(flameSensorPin),
  flameCount(0)
{
  armMotor.attach(armMotorPin);
}

/**
 * If a flame is detected by the arm, extinguish that flame and count it
 */
void ExtinguishingArm::extinguish() {
  if(flameSensor.didDetectFlame()) {
    lower();
    delay(5000); // TODO: Delay 5 seconds (CHANGE THIS IF UNRELIABLE)
    raise();
    flameCount++;
  }
}

/**
 * Sends the current flame count to the vision system. 
 * PRECONDITION: Should only be used after counting all flames
 */
void ExtinguishingArm::reportFlameCount() {
  Enes100Simulation.print("MISSION VALUE: ");
Enes100Simulation.println(flameCount);
}

/**
 * Lower the arm to the extinguishing position
 */
void ExtinguishingArm::lower() {
  armMotor.write(LOW_STATE_ANGLE);
}

/**
 * Raise the arm to the upwards position
 */
void ExtinguishingArm::raise() {
  armMotor.write(HIGH_STATE_ANGLE);
}
