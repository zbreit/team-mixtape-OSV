#include "Navigator.h"
#include "Constants.h"
#include "utils.h"

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
  Enes100.println("Navigating across rocky terrain");
  driveToMiddleLane();
  driveTrain->turnTo(0);
  driveTrain->driveStraight(Field::ROCKY_TERRAIN_X - LocationManager::getBackX());
  Enes100.println("Crossed rocky terrain!!");
}

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

void Navigator::turnUntilOpening() {
  Enes100.println("Turning until an opening...");
  double turnSpeed = (lane == Lane::MIDDLE) ? -0.5 : 0.5;
  
  driveTrain->turn(turnSpeed);
  while(obstaclesStillInTheWay()) {delay(200);}
  driveTrain->stop();
  Enes100.println("Found an opening!!");
}

bool Navigator::obstaclesStillInTheWay() {
  // TODO: Make more accurate
  return (lane == Lane::MIDDLE)
    ? LocationManager::getFrontLeftDistance() < Distance::ULTRASONIC_MAX_RANGE
    : LocationManager::getFrontRightDistance() < Distance::IR_MAX_RANGE;
}

void Navigator::driveToNextLane() {
  Enes100.println("Driving to next lane...");
  double headingInRadians = LocationManager::getCurrentLocation().theta;
  driveTrain->driveStraight(Field::OBSTACLE_LANE_WIDTH / abs(sin(headingInRadians)), LocationManager::getHeading(headingInRadians));
  driveTrain->turnTo(0);
  Enes100.println("Drove to next lane!!!");
}

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
