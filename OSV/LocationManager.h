#ifndef OSV_MANAGER
#define OSV_MANAGER

#include "Constants.h"
#include "utils.h"

/**
 * A collection of static methods to determine the location of the OSV in relation to the field and the obstacles
 */
class LocationManager
{
private:
  LocationManager() {}
  static Coordinate* MISSION_LOCATION;
  static const NewPing frontRightSensor;
  static const NewPing frontLeftSensor;

  /**
   * Delays the program until the vision system updates
   */
  static void waitForLocationUpdate();

  /**
   * @return a pointer to a coordinate corresponding to the mission's location
   */
  static Coordinate *getMissionLocation();

  /**
   * @param sensor a reference to an ultrasonic sensor
   * @return the distance sense by that ultrasonic sensor
   */
  static double getDistance(const NewPing &sensor);

public:
  // OSV Vision system info

  /**
   * @return the current location of the OSV from the vision system
   */
  static Coordinate getCurrentLocation();

  /**
   * @return the x location of the center of the OSV
   */
  static double getCenterX();

  /**
   * @return the y location of the center of the OSV
   */
  static double getCenterY();

  /**
   * Determines the heading of the OSV given a theta value directly from the vision system
   * @param rawThetaVal the heading of the OSV, scaled between -PI and PI radians.
   * @return the angular heading of the OSV, scaled between 0 and 360 degrees.
   */
  static double getHeading(double rawThetaValue);

  /**
   * Determines the angular heading of the OSV
   * @return the angular heading of the OSV, scaled between 0 and 360 degrees.
   */
  static double getHeading();

  /**
   * @return the heading of the OSV to the closest 90 degree increment
   */
  static double getRoundedHeading();

  /**
   * @return x location of front side of OSV when it is horizontal
   */
  static double getFrontX();

  /**
   * @return the y location of the front of the OSV when it is vertical
   */
  static double getTopY();

  /**
   * @return the y location of the back of the OSV when it is vertical
   */
  static double getBottomY();
  static double getBackY();

  /**
   * @return the x location of back side of OSV when it is horizontal
   */
  static double getBackX();

  /**
   * @return x location of right side of OSV when it is vertical
   */
  static double getSideX();

  // OSV Sensor Info

  /**
   * @return the distance retreived by the right front distance sensor, in meters
   */
  static double getFrontRightDistance();

  /**
   * @return the distance retreived by the left front distance sensor, in meters
   */
  static double getFrontLeftDistance();

  /**
   * @return whether there are obstacles to the right of the robot blocking the path
   * to the right of the robot (assuming the robot is facing along the +Y axis)
   */
  static bool obstaclesBlockingTheFront();

  /**
   * @return whether there are obstacles detected by the front right sensor
   */
  static bool obstaclesBlockingTheFrontLeft();

  /**
   * @return whether there are obstacles detected by the front left sensor
   */
  static bool obstaclesBlockingTheFrontRight();

  // Mission information

  /** 
   * @return X of the left of the mission
   */
  static double getMissionX();

  /** 
   * @return Y of the top of the mission
   */
  static double getMissionY();

  /** 
   * @return the x-location of the mission site's center 
   */
  static double getMissionCenterX();

  /** 
   * @return the y-location of the mission site's center
   */
  static double getMissionCenterY();

  /**
   * @return the y-location of the bottom of the mission site
   */
  static double getMissionBottomY();

  /**
   * @return the y-location of the bottom of the mission site
   */
  static double getMissionBackX();
};

#endif
