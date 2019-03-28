#ifndef DRIVE_TRAIN
#define DRIVE_TRAIN

#include "DCMotor.h"

class DriveTrain {
private:
    DCMotor leftMotor;
    DCMotor rightMotor;

public:
    /**
     * Creates a new drive train
     */
    DriveTrain();

    
    void turnTo();
};

#endif
