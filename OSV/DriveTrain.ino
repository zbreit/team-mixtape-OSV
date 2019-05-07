#include "DriveTrain.h"

DriveTrain *DriveTrain::instance = 0;

DriveTrain::DriveTrain() : leftMotor(Pins::LEFT_MOTOR_DIR1, Pins::LEFT_MOTOR_DIR2, Pins::LEFT_MOTOR_PWM, Motors::LEFT_MIN_COMMAND, Motors::LEFT_MAX_COMMAND, Motors::LEFT_IS_REVERSED),
                           rightMotor(Pins::RIGHT_MOTOR_DIR1, Pins::RIGHT_MOTOR_DIR2, Pins::RIGHT_MOTOR_PWM, Motors::RIGHT_MIN_COMMAND, Motors::RIGHT_MAX_COMMAND, Motors::RIGHT_IS_REVERSED)
{
}


DriveTrain *DriveTrain::getInstance()
{
  if (instance == 0)
  {
    instance = new DriveTrain();
  }

  return instance;
}


void DriveTrain::turnTo(double angle)
{
  printPair("Turning to", angle);
  double angularError = getAngularDifference(LocationManager::getHeading(), angle);
  double speed;

  // Continue turning while the error is still significant and the command hasn't timed out
  Timer PIDTimer;
  while (dabs(angularError) > Angle::EQUALITY_THRESHOLD && !PIDTimer.isFinished())
  { 
    // Use basic P-control to determine the output speed, then recalculate the error
    speed = angularError * PIDConstants::TURN_P;
    turn(speed);
    angularError = getAngularDifference(LocationManager::getHeading(), angle);
  }

  if(PIDTimer.isFinished())
  {
    Enes100.println("turnTo() TIMED OUT");
  } 
  else
  {
    printPair("Reached", angle);
  }
  stop();
}


bool DriveTrain::driveStraight(double distance)
{
  return driveStraight(distance, LocationManager::getRoundedHeading());
}


bool DriveTrain::driveStraight(double distance, double angleToMaintain)
{
  printPair("Maintain Angle", angleToMaintain);

  // Determine the desired location and error based on the current location
  Coordinate currentLocation = LocationManager::getCurrentLocation();
  Coordinate desiredLocation = advance(currentLocation, distance);
  double distanceError = distanceBetween(currentLocation, desiredLocation);
  double baseDriveSpeed;

  // Keep driving until the error is within the bounds or the command times out
  Timer PIDTimer;
  while (dabs(distanceError) > Distance::EQUALITY_THRESHOLD && !PIDTimer.isFinished())
  {
    // Use simple P-control to determine the base drive speed
    baseDriveSpeed = distanceError * PIDConstants::DRIVE_P;
    currentLocation = LocationManager::getCurrentLocation();
    distanceError = distanceBetween(currentLocation, desiredLocation);

    // Drive the OSV at a given speed, adjusting the left and right motor outputs to stay aligned with the provided angle
    smartDrive(baseDriveSpeed,
               getAngularDifference(angleToMaintain, LocationManager::getHeading(currentLocation.theta)));

    // If you detect an obstacle, return false
    if (LocationManager::obstaclesBlockingTheFront())
    {
      Enes100.println("Found an obstacle dude");
      stop();
      return false;
    }
  }

  if (PIDTimer.isFinished())
  {
    Enes100.println("DRIVE COMMAND TIMED OUT");
  }
  else
  {
    Enes100.println("DROVE SUCCESSFULLY");
  }
  stop();
  return true;
}


void DriveTrain::smartDrive(double speed, double angularError)
{
  Enes100.print("Angular Error");
  Enes100.println(angularError);

  // Use P-control to determine the left and right side adjustments based on the angular error
  double angleSpeedAdjustment = angularError * PIDConstants::DRIVE_AT_ANGLE_P;
  leftMotor.set(speed + angleSpeedAdjustment);
  rightMotor.set(speed - angleSpeedAdjustment);
}


void DriveTrain::turn(double speed)
{
  rightMotor.set(speed);
  leftMotor.set(-speed);
}


void DriveTrain::stop()
{
  leftMotor.stop();
  rightMotor.stop();
}


void DriveTrain::driveFor(double speed, double timeInMS)
{
  // Turn on motors
  leftMotor.set(speed);
  rightMotor.set(speed);

  delay(timeInMS);

  stop();
}
