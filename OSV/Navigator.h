#ifndef NAVIGATOR
#define NAVIGATOR

#include "LocationManager.h"
#include "DriveTrain.h"
#include "ExtinguishingArm.h"

/**
 * Contains all obstacle and mission navigation functionality
 */
class Navigator
{
private:
  static Navigator *instance;
  DriveTrain *driveTrain;
  ExtinguishingArm *extinguishingArm;
  Lane lane;

  // Navigating to Mission Site

  /**
   * From the landing zone, drive the robot to the middle obstacle lane
   */
  void driveToMiddleLane();

  /**
   * 
   * From a random starting location in the landing zone, drive the robot to the middle lane 
   * and turn towards it
   */
  void prepareToCrossRockyTerrain();

  /**
   * Drive to align the center of the OSV with the mission site's x-coordinate
   */
  void reachMissionSiteX();

  /**
   * Move the OSV from the middle lane to the right lane or from the right lane to the middle lane,
   * depending on the current location of the OSV
   */
  void swapLanes();

  /**
   * Drive between the gaps in obstacles to the next lane
   */
  void driveToNextLane();

  /**
   * DEPRECATED: Used in old version of the turnUntilOpening() method
   * @return whether any obstacles are still in front of the OSV
   */
  bool obstaclesStillInTheWay();

  /**
   * Turn the robot until it is facing towards a gap in the obstacles
   */
  void turnUntilOpening();

  /**
   * After the OSV crosses the obstacles, orient the OSV so that it is ready to detect the first candle
   */
  void goTheDistance();

  /**
   * Counts and extinguishes all flames on the given side.
   * @param sideNum the number corresponding to the given side. sideNum is 0-indexed, meaning
   * when sideNum = 0, the OSV is on the first side.
   */
  void countAndExtinguishSide(int sideNum);

  /**
   * Creates a new Navigator
   */
  Navigator();

public:
  /**
   * Navigate to the mission site
   */
  void navigate();

  /**
   * Goes around the fire pedestal, and counts/extinguishes all flames
   */
  void countAndExtinguishFlames();

  /**
   * @return the one instance of the Navigator
   */
  static Navigator *getInstance();
};

#endif
