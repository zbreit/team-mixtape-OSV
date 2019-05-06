#include "Navigator.h"

/**
 * ===============================
 *   Logic to Create a Navigator 
 * ===============================
 */
// Start off the Navigator instance as null
Navigator *Navigator::instance = 0;

Navigator::Navigator()
{
  driveTrain = DriveTrain::getInstance();
  lane = Lane::MIDDLE;
  extinguishingArm = &ExtinguishingArm(Pins::ARM_MOTOR, Pins::IR_FLAME_SENSOR);
}

Navigator *Navigator::getInstance()
{
  if (instance == 0)
  {
    instance = new Navigator();
  }
  return instance;
}

/**
 * ==========================
 *   Main Navigation Method
 * ==========================
 */


void Navigator::navigate()
{
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

void Navigator::prepareToCrossRockyTerrain()
{
  Enes100.println("Preparing to cross rocky terrain");
  driveToMiddleLane();
  driveTrain->turnTo(0);
  Enes100.println("Ready to cross rocky terrain!!");
}


void Navigator::driveToMiddleLane()
{
  Enes100.println("Navigating to the middle lane");
  lane = Lane::MIDDLE;
  driveTrain->turnTo(90);
  driveTrain->driveStraight(Field::WIDTH / 2 - LocationManager::getCenterY());
  Enes100.println("Reached the middle lane!!");
}


void Navigator::reachMissionSiteX()
{
  // Drive straight until an obstacle is encountered
  Enes100.println("Horizontally aligning to the mission site...");
  while (!driveTrain->driveStraight(Field::OBSTACLE_ENDZONE_X - LocationManager::getBackX()))
  {
    swapLanes();
  }
  Enes100.println("Aligned with the mission site...");
}


void Navigator::swapLanes()
{
  Enes100.println("Swapping Lanes...");
  turnUntilOpening();
  driveToNextLane();
  
  // Swap the instance lane variable
  lane = (lane == Lane::MIDDLE) ? Lane::RIGHT : Lane::MIDDLE;
  Enes100.println("Swapped Lanes!!");
}


void Navigator::turnUntilOpening()
{
  Enes100.println("Turning until an opening...");
  driveTrain->turnTo((lane == Lane::MIDDLE)
                         ? 360 - Angle::LANE_SHIFT
                         : Angle::LANE_SHIFT);
  Enes100.println("Found an opening!!");
}


bool Navigator::obstaclesStillInTheWay()
{
  // TODO: Make more accurate
  return LocationManager::getFrontLeftDistance() < Distance::ULTRASONIC_MAX_RANGE;
}


void Navigator::driveToNextLane()
{
  Enes100.println("Driving to next lane...");
  double headingInRadians = LocationManager::getCurrentLocation().theta;
  driveTrain->driveStraight(Field::OBSTACLE_LANE_WIDTH / abs(sin(headingInRadians)), LocationManager::getHeading(headingInRadians));
  driveTrain->turnTo(0);
  Enes100.println("Drove to next lane!!!");
}

void Navigator::goTheDistance()
{
  Enes100.println("I can find a way....");
  //TODO: add in logic based on whether the OSV is above or below the mission
  driveTrain->turnTo(90);
  driveTrain->driveStraight(LocationManager::getMissionY() - LocationManager::getY() + OSV::WIDTH/2 + OSV::ARM_EXTENSION_LENGTH - FireSite::CANDLE_INSET);
  driveTrain->turnTo(0);
  driveTrain->driveStraight(LocationManager::getMissionX() - LocationManager::getCenterX() + FireSite::EDGE_TO_CANDLE);
  Enes100.println("I can go the distance!!");
}

/**
 * ===========================
 *   Mission Navigation Code 
 * ===========================
 */

void Navigator::countAndExtinguishFlames()
{
  Enes100.println("Counting and extinguishing flames...");

  // Go through every side of the fire site
  for (int sideNum = 0; sideNum < FireSite::SIDE_COUNT; sideNum++)
  {
    countAndExtinguishSide(sideNum);
  }

  // Extinguish and count center flame by approaching from the top of the mission site
  driveTrain->driveStraight(LocationManager::getMissionCenterX() - LocationManager::getCenterX());
  extinguishingArm->extinguish();

  extinguishingArm->reportFlameCount();
  Enes100.println("Counted and extinguished flames...");
}

void Navigator::countAndExtinguishSide(int sideNum)
{
  printPoint("Extinguishing flames on side", sideNum + 1);
  // The angle to which you need to rotate on each cycle around the fire site
  const int angleList[] = {270, 180, 90, 0};

  // Drive to and possibly extinguish the first candle
  Enes100.println("Dealing w/ candle 1...");
  driveTrain->driveStraight(FireSite::EDGE_TO_CANDLE);
  extinguishingArm->extinguish();
  Enes100.println("Finished candle 1!!");

  // Drive to and possibly extinguish the second candle
  Enes100.println("Dealing w/ candle 2...");
  driveTrain->driveStraight(FireSite::CANDLE_TO_CANDLE);
  extinguishingArm->extinguish();
  Enes100.println("Finished candle 2!!");

  // Prepare for the next side
  driveTrain->driveStraight(FireSite::EDGE_TO_CANDLE + (OSV::LENGTH - OSV::WIDTH) / 2. + OSV::ARM_EXTENSION_LENGTH - FireSite::CANDLE_INSET);
  driveTrain->turnTo(angleList[sideNum]);
  Enes100.println("Extinguished all flames on this side!");
}