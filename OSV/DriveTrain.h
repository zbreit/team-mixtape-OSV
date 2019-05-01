#ifndef DRIVE_TRAIN
#define DRIVE_TRAIN

#include "DCMotor.h"
#include "Timer.h"

/**
 * Provides high-level control for the OSV's locomotion
 */
class DriveTrain
{
  private:
    static DriveTrain *instance;
    DCMotor leftMotor;
    DCMotor rightMotor;

    /**
     * Creates a new DriveTrain
     */
    DriveTrain();

  public:
    /**
     * Turns the robot so that its heading matches a given angle
     * @param angle the angle you want your robot to turn to in radians.
     * The angle must be in the range [0, 360]
     */
    void turnTo(double angle);

    /**
     * Drives the robot straight for the specified distance
     * @param distance how far the robot should travel. A positive distance moves
     * the OSV forward and a negative distance moves it backwards.
     */
    bool driveStraight(double distance);

    /**
     * Drives the robot straight for the specified distance
     * @param distance how far the robot should travel. A positive distance moves
     * the OSV forward and a negative distance moves it backwards.
     * @param angleToMaintain the angle at which the OSV should stay while driving forward
     * @return whether or not the OSV traveled the given distance without hitting any obstacles
     */
    bool driveStraight(double distance, double angleToMaintain);

    /**
     * Drives the robot at a given speed, adding slight adjustments to both sides based on the angular error
     * @param speed the desired speed, where -1 is full speed backwards and  
     * +1 is full speed forwards
     * @param angularError the distance, in degrees, between the current and desired heading for the OSV
     * +1 is full speed forwards
     */
    void smartDrive(double speed, double angleToMaintain);

    /**
     * TODO: determine if this should be private
     * Turns the robot at a given speed
     * @param speed the desired speed, where -1 is full speed right and  
     * +1 is full speed left
     */
    void driveFor(double speed, double timeInMS);

    /**
     * Turns off both motors
     */
    void turn(double speed);
    /**
     * Drives the robot at the given speed for the specified duration
     */
    void stop();

    /**
     * @return the single instance of the DriveTrain class
     */
    static DriveTrain *getInstance();
};

#endif
