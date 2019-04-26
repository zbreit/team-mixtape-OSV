#ifndef DRIVE_TRAIN
#define DRIVE_TRAIN

#include "DCMotor.h"

class DriveTrain {
private:
    static DriveTrain* instance;
    DCMotor leftMotor;
    DCMotor rightMotor;

    // Setpoints and outputs for PID
    double calculatedStraightSpeed;
    double calculatedTurnSpeed;
    double currentHeadingError;
    double currentDistanceError;

    // PID Controllers
    PID turnPID;
    PID drivePID;
    PID straightenerPID;

    DriveTrain();
    
    /* Convenience Methods */
    void setUpDriveStraightPIDControllers();
    void tearDownDriveStraightPIDControllers();
    void setUpTurnPIDController();
    void tearDownTurnPIDController();

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
