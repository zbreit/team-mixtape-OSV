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
    delay(10 * 1000); // TODO: Delay 10 seconds (CHANGE THIS IF UNRELIABLE)
    raise();
    flameCount++;
  }
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
