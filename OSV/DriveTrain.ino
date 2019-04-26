#include "DriveTrain.h"
#include "Constants.h"
#include "utils.h"

// Instantiate the orignal drive train instance with a null value
DriveTrain* DriveTrain::instance = 0;

/**
 * Creates a new DriveTrain
 */
DriveTrain::DriveTrain() :
  leftMotor(Pins::LEFT_MOTOR_DIR, Pins::LEFT_MOTOR_PWM, Motors::LEFT_MIN_COMMAND, Motors::LEFT_MAX_COMMAND, Motors::LEFT_IS_REVERSED),
  rightMotor(Pins::RIGHT_MOTOR_DIR, Pins::RIGHT_MOTOR_PWM, Motors::RIGHT_MIN_COMMAND, Motors::RIGHT_MAX_COMMAND, Motors::RIGHT_IS_REVERSED),
  calculatedStraightSpeed(0),
  calculatedTurnSpeed(0),
  currentHeadingError(0),
  currentDistanceError(0),
  turnPID(&PIDSettings::ALWAYS_ZERO, &calculatedTurnSpeed, &currentHeadingError, PIDSettings::TURN_KP, PIDSettings::TURN_KI, PIDSettings::TURN_KD, DIRECT),
  drivePID(&PIDSettings::ALWAYS_ZERO, &calculatedStraightSpeed, &currentDistanceError, PIDSettings::DRIVE_KP, PIDSettings::DRIVE_KI, PIDSettings::DRIVE_KD, DIRECT),
  straightenerPID(&PIDSettings::ALWAYS_ZERO, &calculatedTurnSpeed, &currentHeadingError, PIDSettings::STRAIGHTEN_KP, PIDSettings::STRAIGHTEN_KI, PIDSettings::STRAIGHTEN_KD, DIRECT)
{
  // Remap the PID motor calculations to be between the minimum and maximum possible outputs for the motors
  turnPID.SetOutputLimits(Motors::MIN_COMMAND, Motors::MAX_COMMAND);
  drivePID.SetOutputLimits(Motors::MIN_COMMAND, Motors::MAX_COMMAND);
  straightenerPID.SetOutputLimits(Motors::MIN_COMMAND, Motors::MAX_COMMAND);

  // Turn off all PID Controllers to start off
  turnPID.SetMode(MANUAL);
  drivePID.SetMode(MANUAL);
  straightenerPID.SetMode(MANUAL);
}

/**
 * @return the single instance of the DriveTrain class
 */
DriveTrain* DriveTrain::getInstance() {
  if(instance == 0) {
    instance = new DriveTrain();
  }
  
  return instance;
}

/**
 * Turns the robot so that its heading matches a given angle
 * @param angle the angle you want your robot to turn to in radians.
 * The angle must be in the range [0, 360]
 */
void DriveTrain::turnTo(double angle) {
  Enes100.print("Turning to ");
  Enes100.println(angle);

  setUpTurnPIDController();
  
  while(abs(currentHeadingError) > 0.5) {
    turnPID.Compute();
    turn(calculatedTurnSpeed);
    currentHeadingError = getAngularDifference(LocationManager::getHeading(), angle);
  }

  tearDownTurnPIDController();

  Enes100.print("Reached ");
  Enes100.println(angle);
  stop();
}

/**
 * Drives the robot straight for the specified distance
 * @param distance how far the robot should travel. A positive distance moves
 * the OSV forward and a negative distance moves it backwards.
 */
bool DriveTrain::driveStraight(double distance) {
    return driveStraight(distance, LocationManager::getRoundedHeading());
}

/**
 * Drives the robot straight for the specified distance
 * @param distance how far the robot should travel. A positive distance moves
 * the OSV forward and a negative distance moves it backwards.
 * @param angleToMaintain the angle at which the OSV should stay while driving forward
 * @return whether or not the OSV traveled the given distance without hitting any obstacles
 */
bool DriveTrain::driveStraight(double distance, double angleToMaintain) {
    Enes100.print("Driving ");
    Enes100.print(distance);
    Enes100.print(" m away...");

    setUpDriveStraightPIDControllers();

    // Compute the distance error
    Coordinate currentLocation = LocationManager::getCurrentLocation();
    Coordinate desiredLocation = advance(currentLocation, distance);
    currentDistanceError = distanceBetween(currentLocation, desiredLocation);

    while(abs(currentDistanceError) > Distance::THRESHOLD) {
      // Drive at the calculated speed
      drivePID.Compute();
      smartDrive(calculatedStraightSpeed, 
        getAngularDifference(angleToMaintain, LocationManager::getHeading(currentLocation.theta)));

      // Compute current error
      currentLocation = LocationManager::getCurrentLocation();
      currentDistanceError = distanceBetween(currentLocation, desiredLocation);
      
      // If you detect an obstacle, return false and run teardown code
      if(LocationManager::obstaclesBlockingTheFront()) {
        Enes100.println("Found an obstacle dude");
        tearDownDriveStraightPIDControllers();
        stop();
        return false;
      }
    }
    Enes100.println("Drove successfully!!");

    tearDownDriveStraightPIDControllers();
    stop();
    return true;
}

/**
 * TODO: determine if this should be private
 * Drives the robot at a given speed, adding slight adjustments to both sides based on the angular error
 * @param speed the desired speed, where -1 is full speed backwards and  
 * +1 is full speed forwards
 * @param angularError the distance, in degrees, between the current and desired heading for the OSV
 * +1 is full speed forwards
 */
void DriveTrain::smartDrive(double speed, double angularError) {
  Enes100.print("Angular Error");
  Enes100.println(angularError);

  double angleSpeedAdjustment = angularError * PIDSettings::STRAIGHTEN_KP;
  leftMotor.set(speed + angleSpeedAdjustment);
  rightMotor.set(speed - angleSpeedAdjustment);
}

/**
 * TODO: determine if this should be private
 * Turns the robot at a given speed
 * @param speed the desired speed, where -1 is full speed right and  
 * +1 is full speed left
 */
void DriveTrain::turn(double speed) {
  rightMotor.set(speed);
  leftMotor.set(-speed);
}

/**
 * Turns off both motors
 */
void DriveTrain::stop() {
  leftMotor.stop();
  rightMotor.stop();
}

/**
 * Turns on all PID controllers  control the functionality to drive straight and sets all related output and input values to 0
 */
void DriveTrain::setUpDriveStraightPIDControllers() {
  drivePID.SetMode(MANUAL);
  straightenerPID.SetMode(MANUAL);
  currentDistanceError = 0;
  currentHeadingError = 0;
  calculatedStraightSpeed = 0;
  calculatedTurnSpeed = 0;
}

/**
 * Turns off all PID controllers that control the functionality to drive straight
 */
void DriveTrain::tearDownDriveStraightPIDControllers() {
  drivePID.SetMode(AUTOMATIC);
  straightenerPID.SetMode(AUTOMATIC);

}

/**
 * Turns off all turn-related PID controllers and sets all output and input values to 0
 */
void DriveTrain::setUpTurnPIDController() {
  turnPID.SetMode(MANUAL);
  calculatedStraightSpeed = 0;
  calculatedTurnSpeed = 0;
}

/**
 * Turns off all turn-related PID controllers
 */
void DriveTrain::tearDownTurnPIDController() {
  turnPID.SetMode(AUTOMATIC);
}
