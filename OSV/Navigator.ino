/**
 * Navigate to the mission site
 */
void Navigator::navigate() {
  driveOverRockyTerrain();
  findPathToMissionSite();
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

  // Continue searching for an opening to the mission site that has no obstacles
  // Once this loop is complete, the OSV will (almost always) be in position to drive 
  // straight to align itself with the x-coordinate of the mission site
  bool isApproachingFromTheSide = false;
  Direction travelDirection = chooseDirectionOfTravel();
  int moveCount = 0;
  while(LocationManager::obstaclesAreBlockingTheRight() && moveCount < 4) {
      // If moving in the given direction would cause the OSV to run into a wall, 
      // reverse the direction of travel
      if(LocationManager::cantMoveInDirectionOfTravel(travelDirection)) {
          travelDirection = (travelDirection == Direction::UP)
            ? Direction::DOWN 
            : Direction::UP;
          verticallyAlignToMissionSite(); // Return to the y-location of fire pedstal
      }

      shiftInDirectionOfTravel(travelDirection);

      // If this loop runs, we will approach the fire pedestal from the side
      isApproachingFromTheSide = true;
      moveCount++;
  }

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
