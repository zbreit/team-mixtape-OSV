#ifndef MOTOR
#define MOTOR

class DCMotor {
private:
    const byte directionPin; // The pin that controls the motor's direction
    const byte speedPin; // The pin that controls the speed of the motor
public:
    /**
     * Creates a new motor
     * @param directionPin the pin that controls the motor's direction
     * @param speedPin the pin that controls the motor's speed
     */
    DCMotor(byte directionPin, byte speedPin);

    /**
     * Sets the motor to a desired speed. +1.0 is full-speed forward 
     * and -1.0 is full-speed backwards.
     * @param speed the desired speed of the robot, specified as a decimal
     * between -1.0 and 1.0
     */
    void set(double speed);
};

#endif
