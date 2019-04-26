/**
 * Navigate to the mission site
 */
void Navigator::navigate() {
  prepareToCrossRockyTerrain();
  reachMissionSiteX();
  goTheDistance();
  driveTrain->stop();
}

/**
 * =============================
 *   Navigation Helper Methods
 * =============================
 */

/**
 * From a random starting location in the landing zone, drive the robot a little bit the rocky terrain
 */
void Navigator::prepareToCrossRockyTerrain() {
  Enes100.println("Preparing to cross rocky terrain");
  driveToMiddleLane();
  driveTrain->turnTo(0);
  Enes100.println("Crossed rocky terrain!!");
}

/**
 * From the landing zone, drive the robot to the middle obstacle lane
 */
void Navigator::driveToMiddleLane() {
  Enes100.println("Navigating to the middle lane");
  lane = Lane::MIDDLE;
  driveTrain->turnTo(90);
  driveTrain->driveStraight(Field::WIDTH / 2 - LocationManager::getY());
  Enes100.println("Reached the middle lane!!");
}

/**
 * Drive to align the center of the OSV with the mission site's x-coordinate
 */
void Navigator::reachMissionSiteX() {
  // Drive straight until an obstacle is encountered
  Enes100.println("Horizontally aligning to the mission site...");
  while(!driveTrain->driveStraight(Field::OBSTACLE_ENDZONE_X - LocationManager::getBackX())) {
    swapLanes();
  }
  Enes100.println("Aligned with the mission site...");
}

/**
 * Move the OSV from the middle lane to the right lane or from the right lane to the middle lane,
 * depending on the current location of the OSV
 */
void Navigator::swapLanes() {
  Enes100.println("Swapping Lanes...");
  turnUntilOpening();
  driveToNextLane();
  
  if(lane == Lane::MIDDLE) {
    lane = Lane::RIGHT;
  } else {
    lane = Lane::MIDDLE;
  }
  Enes100.println("Swapped Lanes!!");
}

/**
 * Turn the robot until it is facing towards a gap in the obstacles
 */
void Navigator::turnUntilOpening() {
  Enes100.println("Turning until an opening...");
  driveTrain->turnTo((lane == Lane::MIDDLE)
    ? 360 - Angle::LANE_SHIFT
    : Angle::LANE_SHIFT);
  Enes100.println("Found an opening!!");
}

/**
 * DEPRECATED: Used in old version of the turnUntilOpening() method
 * Returns whether any obstacles are still in front of the OSV
 */
bool Navigator::obstaclesStillInTheWay() {
  // TODO: Make more accurate
  return LocationManager::getFrontLeftDistance() < Distance::ULTRASONIC_MAX_RANGE
}

/**
 * Drive between the gaps in obstacles to the next lane
 */
void Navigator::driveToNextLane() {
  Enes100.println("Driving to next lane...");
  double headingInRadians = LocationManager::getCurrentLocation().theta;
  driveTrain->driveStraight(Field::OBSTACLE_LANE_WIDTH / abs(sin(headingInRadians)), LocationManager::getHeading(headingInRadians));
  driveTrain->turnTo(0);
  Enes100.println("Drove to next lane!!!");
}

/**
 * After the OSV crosses the obstacles, orient the OSV so that it is ready to detect the first candle
 */
void Navigator::goTheDistance() {
  Enes100.println("I can find a way....");
  //TODO: add in logic based on whether the OSV is above or below the mission
  driveTrain->turnTo(90);
  driveTrain->driveStraight(LocationManager::getMissionY() - LocationManager::getBottomY() - OSV::WIDTH + OSV::ARM_EXTENSION_LENGTH - FireSite::CANDLE_INSET);
  driveTrain->turnTo(0);
  driveTrain->driveStraight(LocationManager::getMissionX() - LocationManager::getX() + FireSite::EDGE_TO_CANDLE);
  Enes100.println("I can go the distance!!");
}


/**
 * ===========================
 *   Mission Navigation Code 
 * ===========================
 */

/**
 * Goes around the fire pedestal, and counts/extinguishes all flames
 */
void Navigator::countAndExtinguishFlames() {
  Enes100.println("Counting and extinguishing flames...");

  // The angle to which you need to rotate on each cycle around the fire site
  int angleList[] = { 270, 180, 90, 0 };

  // Go through every side of the fire site
  for(int sideNum = 0; sideNum < FireSite::SIDE_COUNT; sideNum++) {
    // Drive to and possibly extinguish the first candle
    driveTrain->driveStraight(FireSite::EDGE_TO_CANDLE);
    extinguishingArm->extinguish();
    
    // Drive to and possibly extinguish the second candle
    driveTrain->driveStraight(FireSite::CANDLE_TO_CANDLE);
    extinguishingArm->extinguish();

    // Prepare for the next side
    driveTrain->driveStraight(FireSite::EDGE_TO_CANDLE + (OSV::LENGTH - OSV::WIDTH) / 2. + OSV::ARM_EXTENSION_LENGTH - FireSite::CANDLE_INSET);
    driveTrain->turnTo(angleList[sideNum]);
  }

  // Extinguish and count center flame
  driveTrain->driveStraight(LocationManager::getMissionCenterX() - LocationManager::getX());
  extinguishingArm->extinguish();

  extinguishingArm->reportFlameCount();
  Enes100.println("Counted and extinguished flames...");
}
 

/**
 * ===============================
 *   Logic to Create a Navigator 
 * ===============================
 */

/**
 * Creates a new Navigator
 */
Navigator::Navigator() {
  driveTrain = DriveTrain::getInstance();
  lane = Lane::MIDDLE;
  extinguishingArm = &ExtinguishingArm(Pins::ARM_MOTOR, Pins::IR_FLAME_SENSOR);
}

// Start off the Navigator instance as null
Navigator* Navigator::instance = 0;

/**
 * @return the one instance of the Navigator
 */
Navigator* Navigator::getInstance() {
  if(instance == 0) {
    instance = new Navigator();
  }
  return instance;
}
