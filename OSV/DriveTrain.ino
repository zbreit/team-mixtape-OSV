DriveTrain* DriveTrain::instance = 0;

/**
 * Creates a new DriveTrain
 */
DriveTrain::DriveTrain() :
  leftMotor(Pins::LEFT_MOTOR_DIR, Pins::LEFT_MOTOR_PWM),
  rightMotor(Pins::RIGHT_MOTOR_DIR, Pins::RIGHT_MOTOR_PWM)
{}

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
  double angularError = getAngularDifference(LocationManager::getHeading(), angle);
  double speed;
  
  while(abs(angularError) > 0.5) {
    speed = angularError * PIDConstants::TURN_P;
    turn(speed);
    angularError = getAngularDifference(LocationManager::getHeading(), angle);
  }
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
    Enes100.print("Maintain Angle: ");
    Enes100.println(angleToMaintain);
    Coordinate currentLocation = LocationManager::getCurrentLocation();
    Coordinate desiredLocation = advance(currentLocation, distance);
    double distanceError = distanceBetween(currentLocation, desiredLocation);
    double speed;
    while(abs(distanceError) > Distance::THRESHOLD) {
      speed = distanceError * PIDConstants::DRIVE_P;
      currentLocation = LocationManager::getCurrentLocation();
      distanceError = distanceBetween(currentLocation, desiredLocation);
      smartDrive(speed, 
        getAngularDifference(angleToMaintain, LocationManager::getHeading(currentLocation.theta)));

      // If you detect an obstacle, return false
      if(LocationManager::obstaclesBlockingTheFront()) {
        Enes100.println("Found an obstacle dude");
        stop();
        return false;
      }
    }
    Enes100.println("DROVE SUCCESSFULLY");
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
  double angleSpeedAdjustment = angularError * PIDConstants::DRIVE_AT_ANGLE_P;
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
