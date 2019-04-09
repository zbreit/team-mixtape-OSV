/**
 * Navigate to the mission site
 */
void Navigator::navigate() {
  driveOverRockyTerrain();
  verticallyAlignToMissionSite();
  driveToMissionSite();
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
  Serial.println("Navigating to rocky terrain");
  driveTrain->turnTo(0);
  driveTrain->driveStraight(Field::ROCKY_TERRAIN_X - LocationManager::getBackX() + OSV::LENGTH / 2);
  Serial.println("Crossed rocky terrain!!");
}

/**
 * Search for horiztonal paths to the mission site
 */
bool Navigator::findPathToMissionSite() {
  Serial.println("Finding Path to Mission Site");
  verticallyAlignToMissionSite();
}

/**
 * From a random starting location in the landing zone, drive the robot a little bit the rocky terrain
 */
void Navigator::driveToMissionSite() {
  driveTrain->turnTo(0);
  driveTrain->driveStraight(LocationManager::getMissionX() - LocationManager::getFrontX());
}

/**
 * Vertically align the robot to the mission site
 */
void Navigator::verticallyAlignToMissionSite() {
  // Vertically lign the center of the OSV with the center of the mission site
  driveTrain->turnTo(90);
  driveTrain->driveStraight(LocationManager::getMissionCenterY() - LocationManager::getY());
}


/**
 * Vertically align the robot to the mission site
 */
Direction Navigator::chooseDirectionOfTravel() {
  return LocationManager::getY() < (Field::WIDTH / 2.) 
    ? Direction::UP 
    : Direction::DOWN;
}

/**
 * Vertically align the robot to the mission site
 */
void Navigator::shiftInDirectionOfTravel(Direction direction) {
  // Shift the OSV over by one length
  if(direction == Direction::UP) {
      driveTrain->driveStraight(OSV::LENGTH);
  } else {
      driveTrain->driveStraight(-OSV::LENGTH);
  }
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
