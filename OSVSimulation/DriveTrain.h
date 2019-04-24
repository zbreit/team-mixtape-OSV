#ifndef DRIVE_TRAIN
#define DRIVE_TRAIN

#include "DCMotor.h"

class DriveTrain {
private:
    static DriveTrain* instance;
    DCMotor leftMotor;
    DCMotor rightMotor;
    DriveTrain();
    
public:
    void turnTo(double angle);
    bool driveStraight(double distance);
    bool driveStraight(double distance, double angleToMaintain);
    void smartDrive(double speed, double angleToMaintain);
    void turn(double speed);
    void stop();
    static DriveTrain* getInstance();
};

#endif
