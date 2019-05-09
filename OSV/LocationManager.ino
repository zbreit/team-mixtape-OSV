#include "LocationManager.h"

/**
 * =======================
 *   STATIC MEMBER SETUP
 * =======================
 */
const NewPing LocationManager::frontRightSensor(Pins::RIGHT_ULTRASONIC_TRIGGER, Pins::RIGHT_ULTRASONIC_ECHO);
const NewPing LocationManager::frontLeftSensor(Pins::LEFT_ULTRASONIC_TRIGGER, Pins::LEFT_ULTRASONIC_ECHO);
Coordinate *LocationManager::MISSION_LOCATION = 0;

/**
 * =========================
 *   CONVENIENCE FUNCTIONS
 * =========================
 */

void LocationManager::waitForLocationUpdate()
{
  while (!Enes100.updateLocation()) {}
}

/**
 * ======================
 *   VISION SYSTEM INFO
 * ======================
 */

Coordinate LocationManager::getCurrentLocation()
{
  waitForLocationUpdate();
  return Enes100.location;
}


Coordinate* LocationManager::getCenter()
{
  // Polls for the location of the aruco marker, and extends that distance
  // by the offset of the marker from the center of the OSV
  Coordinate currentLocation = getCurrentLocation();
  return &advance(currentLocation, OSV::ARUCO_MARKER_CENTER_OFFSET);
}


double LocationManager::getCenterX()
{
  return getCenter()->x;
}


double LocationManager::getCenterY()
{
  return getCenter()->y;
}


double LocationManager::getSideX()
{
  return getCenterX() + (OSV::WIDTH / 2);
}


double LocationManager::getFrontX()
{
  return getCenterX() + (OSV::LENGTH / 2);
}


double LocationManager::getBackX()
{
  return getCenterX() - (OSV::LENGTH / 2);
}


double LocationManager::getTopY()
{
  return getCenterY() + (OSV::LENGTH / 2);
}


double LocationManager::getBottomY()
{
  return getCenterY() - (OSV::LENGTH / 2);
}


double LocationManager::getHeading()
{
  return getHeading(getCurrentLocation().theta);
}


double LocationManager::getHeading(double rawThetaValue)
{
  return (rawThetaValue >= 0)
             ? radiansToDegrees(rawThetaValue)
             : 360 + radiansToDegrees(rawThetaValue);
}


double LocationManager::getRoundedHeading()
{
  double heading = getHeading();

  if (heading > 45. && heading <= 135.)
  {
    // If the angle is between 45 and 135, return 90
    return 90.;
  }
  else if (heading > 135. && heading <= 225.)
  {
    // If the angle is between 135 and 225, return 180
    return 180.;
  }
  else if (heading > 225. && heading <= 315.)
  {
    // If the angle is between 225 and 315, return 180
    return 270.;
  }
  else
  {
    // If the angle is between 315 and 45, return 0
    return 0.;
  }
}

/**
 * ========================
 *   DISTANCE SENSOR INFO
 * ========================
 */

double LocationManager::getFrontLeftDistance()
{
  return getDistance(frontLeftSensor);
}


double LocationManager::getFrontRightDistance()
{
  return getDistance(frontRightSensor);
}


double LocationManager::getDistance(const NewPing &sensor)
{
  unsigned int medianTimePerPing = sensor.ping_median(Distance::SAMPLE_NUMBER);
  unsigned int sensedDistance = sensor.convert_cm(medianTimePerPing);

  // Return an arbitrarily large value if the sensor reading is a 0.
  // This is due to an intricacy with the NewPing library, where out of range values
  // are assigned to 0 instead of a larger value.
  return (sensedDistance == 0) ? 100000 : sensedDistance;
}


bool LocationManager::obstaclesBlockingTheFront()
{
  return obstaclesBlockingTheFrontLeft() || obstaclesBlockingTheFrontRight();
}


bool LocationManager::obstaclesBlockingTheFrontRight()
{
  return getFrontRightDistance() < Distance::SAFE_FRONT_DISTANCE;
}


bool LocationManager::obstaclesBlockingTheFrontLeft()
{
  return getFrontLeftDistance() < Distance::SAFE_FRONT_DISTANCE;
}

/**
 * ========================
 *   MISSION LOCATION INFO
 * ========================
 */

Coordinate *LocationManager::getMissionLocation()
{
  if (MISSION_LOCATION == 0)
  {
    waitForLocationUpdate();
    MISSION_LOCATION = &Enes100.destination;
  }
  return MISSION_LOCATION;
}


double LocationManager::getMissionCenterY()
{
  return getMissionLocation()->y;
}


double LocationManager::getMissionCenterX()
{
  return getMissionLocation()->x;
}


double LocationManager::getMissionLeftX()
{
  return getMissionCenterX() - FireSite::RADIUS;
}


double LocationManager::getMissionTopY()
{
  return getMissionCenterY() + FireSite::RADIUS;
}


double LocationManager::getMissionBottomY()
{
  return getMissionCenterY() - FireSite::RADIUS;
}


double LocationManager::getMissionBackX()
{
  return getMissionCenterX() + FireSite::RADIUS;
}
