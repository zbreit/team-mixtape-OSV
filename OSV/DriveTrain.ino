#include "DriveTrain.h"

DriveTrain *DriveTrain::instance = 0;

DriveTrain::DriveTrain() : leftMotor(Pins::LEFT_MOTOR_DIR, Pins::LEFT_MOTOR_PWM, Motors::LEFT_MIN_COMMAND, Motors::LEFT_MAX_COMMAND, Motors::LEFT_IS_REVERSED),
                           rightMotor(Pins::RIGHT_MOTOR_DIR, Pins::RIGHT_MOTOR_PWM, Motors::RIGHT_MIN_COMMAND, Motors::RIGHT_MAX_COMMAND, Motors::RIGHT_IS_REVERSED)
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
  Enes100.print("Turning to ");
  Enes100.println(angle);
  double angularError = getAngularDifference(LocationManager::getHeading(), angle);
  double speed;

  Timer PIDTimer;
  while (dabs(angularError) > Angle::EQUALITY_THRESHOLD && !PIDTimer.isFinished())
  {
    speed = angularError * PIDConstants::TURN_P;
    turn(speed);
    angularError = getAngularDifference(LocationManager::getHeading(), angle);
  }
  if(PIDTimer.isFinished())
  {
    Enes100.print("COMMAND TIMED OUT");
  } 
  else
  {
    Enes100.print("Reached ");
    Enes100.println(angle);
  }
  stop();
}


bool DriveTrain::driveStraight(double distance)
{
  return driveStraight(distance, LocationManager::getRoundedHeading());
}


bool DriveTrain::driveStraight(double distance, double angleToMaintain)
{
  Enes100.print("Maintain Angle: ");
  Enes100.println(angleToMaintain);

  // Determine the desired location based on the current location
  Coordinate currentLocation = LocationManager::getCurrentLocation();
  Coordinate desiredLocation = advance(currentLocation, distance);

  // Keep driving until the error is within the bounds
  double distanceError = distanceBetween(currentLocation, desiredLocation);
  double speed;
  Timer PIDTimer;
  while (dabs(distanceError) > Distance::EQUALITY_THRESHOLD && !PIDTimer.isFinished())
  {
    speed = distanceError * PIDConstants::DRIVE_P;
    currentLocation = LocationManager::getCurrentLocation();
    distanceError = distanceBetween(currentLocation, desiredLocation);

    // Drive the OSV at a given speed, adjusting the left and right motor outputs to stay aligned with the provided angle
    smartDrive(speed,
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
