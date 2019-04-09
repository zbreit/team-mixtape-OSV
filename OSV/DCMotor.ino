/**
 * Creates a new motor
 * @param directionPin the pin that controls the motor's direction
 * @param speedPin the pin that controls the motor's speed
 * @param speedCap the fastest speed the OSV can travel. Should be a value between 0.0 and +1.0
 */
DCMotor::DCMotor(pin directionPin, pin speedPin, double speedCap) :
  directionPin(directionPin),
  speedPin(speedPin),
  speedCap(speedCap)
{}

/**
 * Sets the motor to a desired speed. +1.0 is full-speed forward 
 * and -1.0 is full-speed backwards.
 * @param speed the desired speed of the robot, specified as a decimal
 * between -1.0 and 1.0
 */
void DCMotor::set(double speed) {
  // Turn on the direction pin if the motor is driving forward, and set it to 0 otherwise
  int direction = (speed > 0.0) ? HIGH : LOW;
  digitalWrite(directionPin, direction);

  // Set the speed of the motor
  int desiredSpeed = abs(speed) * 255 * speedCap;
  analogWrite(desiredSpeed, speed);
}

/**
 * Stops the motor from running
 */
void DCMotor::stop() {
  digitalWrite(speedPin, LOW);
}
