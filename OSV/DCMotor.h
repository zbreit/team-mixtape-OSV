#ifndef MOTOR
#define MOTOR

#include "utils.h"

/**
 * Wrapper class to control motors on the Arduino Romeo. Provides methods to reverse motor polarity, set min and max output. 
 */
class DCMotor
{
  private:
    const pin directionPin;  // The pin that controls the motor's direction
    const pin speedPin;      // The pin that controls the speed of the motor
    const double speedCap;   // The fastest possible speed the motor should travel
    const double speedFloor; // The slowest possible speed the motor should travel
    const bool isReversed;   // Whether or not the motor direction should be flipped
  public:
    /**
     * Creates a new motor
     * @param directionPin the pin that controls the motor's direction
     * @param speedPin the pin that controls the motor's speed
     * @param speedFloor the slowest speed the OSV can travel. Should be a value between 0.0 and +1.0. Should be less than speedCap.
     * @param speedCap the fastest speed the OSV can travel. Should be a value between 0.0 and +1.0. Should be greater than speedFloor
     * @param isReversed true if the motors are connected in reverse, false otherwise.
     */
    DCMotor(pin directionPin, pin speedPin, double speedFloor = 1.0, double speedCap = 0., bool isReversed = false);

    /**
     * Sets the motor to a desired speed. +1.0 is full-speed forward 
     * and -1.0 is full-speed backwards.
     * @param speed the desired speed of the robot, specified as a decimal
     * between -1.0 and 1.0
     */
    void set(double speed);

    /**
     * Stops the motor from running
     */
    void stop();
};

#endif
