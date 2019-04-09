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


/**
 * Stops the motor from running
 */

