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
  //TODO: add in a stop command after this
}

/**
 * Drives the robot straight for the specified distance
 * @param distance how far the robot should travel. A positive distance moves
 * the OSV forward and a negative distance moves it backwards.
 */
void DriveTrain::driveStraight(double distance) {
    Coordinate currentLocation = LocationManager::getCurrentLocation();
    Coordinate desiredLocation = advanceForward(currentLocation, distance);
    double distanceError = distanceBetween(currentLocation, desiredLocation);
    double speed;
    
    while(distanceError > Distance::THRESHOLD) {
      speed = distanceError * PIDConstants::DRIVE_P;
      currentLocation = LocationManager::getCurrentLocation();
      distanceError = distanceBetween(currentLocation, desiredLocation);
      drive(speed);

      Serial.print("Error: ");
      Serial.println(distanceError);
      Serial.print("Speed: ");
      Serial.println(speed);
      Serial.print("Current Y: ");
      Serial.println(currentLocation.y);
      Serial.println();
    }
    Serial.println("DROVE SUCCESSFULLY");
    //TODO: ADD THE STOP() BACK IN AFTER FINISHING SIMULATION
//    stop();
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
