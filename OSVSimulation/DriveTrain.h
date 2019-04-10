#ifndef DRIVE_TRAIN
#define DRIVE_TRAIN

#include "DCMotor.h"

class DriveTrain {
private:
    static DriveTrain* instance;
    DCMotor leftMotor;
    DCMotor rightMotor;
    DriveTrain();
    
    /* Private convenience methods */
    void setBothSidesTo(double speed);
    
public:
    void turnTo(double angle);
    bool driveStraight(double distance);
    void drive(double speed=1);
    void turn(double speed);
    void stop();
    static DriveTrain* getInstance();

};

#endif
