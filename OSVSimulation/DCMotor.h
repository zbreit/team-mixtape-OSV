#ifndef MOTOR
#define MOTOR

class DCMotor {
private:
    const pin directionPin; // The pin that controls the motor's direction
    const pin speedPin; // The pin that controls the speed of the motor
    const double speedCap; // The fastest possible speed the motor should travel
public:
    DCMotor(pin directionPin, pin speedPin, double speedCap=1.0);
    void set(double speed);
    void stop();
};

#endif
