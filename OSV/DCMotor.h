#ifndef MOTOR
#define MOTOR

class DCMotor {
private:
    const pin directionPin; // The pin that controls the motor's direction
    const pin speedPin; // The pin that controls the speed of the motor
    const double speedCap; // The fastest possible speed the motor should travel
    const double speedFloor; // The slowest possible speed the motor should travel
    const bool isReversed; // Whether or not the motor direction should be flipped
public:
    DCMotor(pin directionPin, pin speedPin, double speedFloor=1.0, double speedCap=0., bool isReversed=true);
    void set(double speed);
    void stop();
};

#endif
