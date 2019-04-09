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
  double angularError = getAngularDifference(LocationManager::getHeading(), angle);
  double speed;
  
  while(abs(angularError) > 0.5) {
    speed = angularError * PIDConstants::TURN_P;
    turn(speed);
    angularError = getAngularDifference(LocationManager::getHeading(), angle);
  }
  Serial.print("Reached angle ");
  Serial.println(angle);
  //TODO: REPLACE WITH JUST STOP() AFTER FINISHING SIMULATION
  DriveTrain* driveTrain = instance;
  TankSimulation.turnOffMotors();
}

/**
 * Drives the robot straight for the specified distance
 * @param distance how far the robot should travel. A positive distance moves
 * the OSV forward and a negative distance moves it backwards.
 */
void DriveTrain::driveStraight(double distance) {
    Coordinate currentLocation = LocationManager::getCurrentLocation();
    Coordinate desiredLocation = advance(currentLocation, distance);
    
    int directionalMultiplier = (distance > 0) ? 1 : -1;
    double distanceError = directionalMultiplier * distanceBetween(currentLocation, desiredLocation);
    double speed;
    
    while(abs(distanceError) > Distance::THRESHOLD) {
      speed = distanceError * PIDConstants::DRIVE_P;
      currentLocation = LocationManager::getCurrentLocation();
      distanceError = directionalMultiplier * distanceBetween(currentLocation, desiredLocation);
      drive(speed);
    }
    Serial.println("DROVE SUCCESSFULLY");
    //TODO: REPLACE WITH JUST STOP() AFTER FINISHING SIMULATION
    DriveTrain* driveTrain = instance;
    TankSimulation.turnOffMotors();
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
  TankSimulation.setRightMotorPWM(speed * 255);
  TankSimulation.setLeftMotorPWM(-speed * 255);
}

/**
 * Turns off both motors
 */


/**
 * Sets both sides of the drive train to a desired speed. +1.0 is full-speed forward 
 * and -1.0 is full-speed backwards.
 * @param speed the desired speed of the robot, specified as a decimal
 * between -1.0 and 1.0
 */
void DriveTrain::setBothSidesTo(double speed) {
  TankSimulation.setLeftMotorPWM(speed);
  TankSimulation.setRightMotorPWM(speed);
}
