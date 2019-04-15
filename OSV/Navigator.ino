/**
 * Navigate to the mission site
 */
void Navigator::navigate() {
  driveOverRockyTerrain();
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
void Navigator::driveOverRockyTerrain() {
  Serial.println("Navigating across rocky terrain");
  driveToMiddleLane();
  driveTrain->turnTo(0);
  driveTrain->driveStraight(Field::ROCKY_TERRAIN_X - LocationManager::getBackX());
  Serial.println("Crossed rocky terrain!!");
}

void Navigator::driveToMiddleLane() {
  Serial.println("Navigating to the middle lane");
  lane = Lane::MIDDLE;
  driveTrain->turnTo(90);
  driveTrain->driveStraight(Field::WIDTH / 2 - LocationManager::getY());
  Serial.println("Reached the middle lane!!");
}

/**
 * Drive to align the center of the OSV with the mission site's x-coordinate
 */
void Navigator::reachMissionSiteX() {
  // Drive straight until an obstacle is encountered
  Serial.println("Horizontally aligning to the mission site...");
  while(!driveTrain->driveStraight(LocationManager::getMissionX() - LocationManager::getFrontX())) {
    swapLanes();
  }
  Serial.println("Aligned with the mission site...");
}

void Navigator::swapLanes() {
  Serial.println("Swapping Lanes...");
  turnUntilOpening();
  driveToNextLane();
  
  if(lane == Lane::MIDDLE) {
    lane = Lane::RIGHT;
  } else {
    lane = Lane::RIGHT;
  }
  Serial.println("Swapped Lanes!!");
}

void Navigator::turnUntilOpening() {
  Serial.println("Turning until an opening...");
  double turnSpeed = (lane == Lane::MIDDLE) ? -0.5 : 0.5;
  
  driveTrain->turn(turnSpeed);
  while(obstaclesStillInTheWay()) {delay(200);}
  driveTrain->stop();
  Serial.println("Found an opening!!");
}

bool Navigator::obstaclesStillInTheWay() {
//  Serial.print("Left Distance: ");
//  Serial.println(LocationManager::getFrontLeftDistance());
//  Serial.print("Right Distance: ");
//  Serial.println(LocationManager::getFrontRightDistance());
  // TODO: Make more accurate
  return (lane == Lane::MIDDLE)
    ? LocationManager::getFrontLeftDistance() < Distance::ULTRASONIC_MAX_RANGE
    : LocationManager::getFrontRightDistance() < Distance::IR_MAX_RANGE;
}

void Navigator::driveToNextLane() {
  Serial.println("Driving to next lane...");
  driveTrain->driveStraight(Field::OBSTACLE_LANE_WIDTH / abs(sin(LocationManager::getCurrentLocation().theta))); // TODO: Compute actual required distance
  driveTrain->turnTo(0);
  Serial.println("Drove to next lane!!!");
}

void Navigator::goTheDistance() {
  Serial.println("I can find a way....");
  double heightDifference = LocationManager::getY() - LocationManager::getMissionCenterY();
  if(abs(heightDifference) > Distance::REACHED_MISSION_SITE) {
    driveTrain->driveStraight(LocationManager::getMissionCenterX() - LocationManager::getX());
    driveTrain->turnTo((heightDifference > 0) ? 270 : 90);
    driveTrain->driveStraight((heightDifference > 0)
      ? abs(LocationManager::getBottomY() - LocationManager::getMissionY())
      : abs(LocationManager::getTopY() - LocationManager::getMissionBottomY()));
  }
  Serial.println("I can go the distance!!");
}

/**
 * ============================
 *   Creating Navigator Logic
 * ============================
 */

/**
 * Creates a new Navigator
 */
Navigator::Navigator() {
  driveTrain = DriveTrain::getInstance();
  lane = Lane::MIDDLE;
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
