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
  Serial.print("Turning to ");
  Serial.println(angle);
  double angularError = getAngularDifference(LocationManager::getHeading(), angle);
  double speed;
  
  while(abs(angularError) > 0.5) {
    speed = angularError * PIDConstants::TURN_P;
    turn(speed);
    angularError = getAngularDifference(LocationManager::getHeading(), angle);
  }
  Serial.print("Reached ");
  Serial.println(angle);
  //TODO: REPLACE WITH JUST STOP() AFTER FINISHING SIMULATION
  DriveTrain* driveTrain = instance;
  driveTrain->stop();
}

/**
 * Drives the robot straight for the specified distance
 * @param distance how far the robot should travel. A positive distance moves
 * the OSV forward and a negative distance moves it backwards.
 */
bool DriveTrain::driveStraight(double distance) {
    Coordinate currentLocation = LocationManager::getCurrentLocation();
    Coordinate desiredLocation = advance(currentLocation, distance);
    double distanceError = distanceBetween(currentLocation, desiredLocation);
    double speed;
    
    DriveTrain* driveTrain = instance; // TODO: Remove after simulation
    
    while(abs(distanceError) > Distance::THRESHOLD) {
      speed = distanceError * PIDConstants::DRIVE_P;
      currentLocation = LocationManager::getCurrentLocation();
      distanceError = distanceBetween(currentLocation, desiredLocation);
      drive(speed);

      // If you detect an obstacle, return false
      if(LocationManager::obstaclesBlockingTheFront()) {
        Serial.println("Found an obstacle dude");
        driveTrain->stop(); //TODO: REPLACE WITH JUST STOP() AFTER FINISHING SIMULATION
        return false;
      }
    }
    Serial.println("DROVE SUCCESSFULLY");
    //TODO: REPLACE WITH JUST STOP() AFTER FINISHING SIMULATION
    driveTrain->stop();
    return true;
}

/**
 * TODO: determine if this should be private
 * Drives the robot at a given speed
 * @param speed the desired speed, where -1 is full speed backwards and  
 * +1 is full speed forwards
 */
void DriveTrain::drive(double speed) {
  // TODO: This argument SHOULD be replaced with just 'speed' when simulation testing is over
  setBothSidesTo(speed * 255);
}

/**
 * TODO: determine if this should be private
 * Turns the robot at a given speed
 * @param speed the desired speed, where -1 is full speed right and  
 * +1 is full speed left
 */
void DriveTrain::turn(double speed) {
  // TODO: These arguments SHOULD be replaced with just 'speed' when simulation testing is over
  rightMotor.set(speed * 255);
  leftMotor.set(-speed * 255);
}

/**
 * Turns off both motors
 */
void DriveTrain::stop() {
  leftMotor.stop();
  rightMotor.stop();
}

/**
 * Sets both sides of the drive train to a desired speed. +1.0 is full-speed forward 
 * and -1.0 is full-speed backwards.
 * @param speed the desired speed of the robot, specified as a decimal
 * between -1.0 and 1.0
 */
void DriveTrain::setBothSidesTo(double speed) {
  leftMotor.set(speed);
  rightMotor.set(speed);
}
