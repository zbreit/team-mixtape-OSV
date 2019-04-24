/**
 * =======================
 *   STATIC MEMBER SETUP
 * =======================
 */
const NewPing LocationManager::frontRightSensor(Pins::RIGHT_ULTRASONIC_TRIGGER, Pins::RIGHT_ULTRASONIC_ECHO);
const NewPing LocationManager::frontLeftSensor(Pins::LEFT_ULTRASONIC_TRIGGER, Pins::LEFT_ULTRASONIC_ECHO);
Coordinate* LocationManager::MISSION_LOCATION = 0;

/**
 * =======================
 *   CONVENIENCE FUNCTION
 * =======================
 */

/**
 * Delays the program until the vision system updates
 */
static void LocationManager::waitForLocationUpdate() {
  //TODO: might need to add in a timer to prevent an infinite loop
  while(!Enes100.updateLocation()) {}
}

/**
 * ======================
 *   VISION SYSTEM INFO
 * ======================
 */

/**
 * Gets the current location of the OSV from the vision system
 * @return a coordinate with the OSV's current position
 */
static Coordinate LocationManager::getCurrentLocation() {
  waitForLocationUpdate();
  return Enes100.location;
}

/**
 * @return the x location of the center of the OSV
 */
static double LocationManager::getX() {
    return getCurrentLocation().x;
}

/**
 * @return the y location of the center of the OSV
 */
static double LocationManager::getY() {
    return getCurrentLocation().y;
}

/**
 * @return x location of right side of OSV when it is vertical
 */
static double LocationManager::getSideX() {
    return getX() + (OSV::WIDTH / 2);
}

/**
 * @return x location of front side of OSV when it is horizontal
 */
static double LocationManager::getFrontX() {
    return getX() + (OSV::LENGTH / 2);
}

/**
 * @return the x location of back side of OSV when it is horizontal
 */
static double LocationManager::getBackX() {
    return getX() - (OSV::LENGTH / 2);
}

/**
 * @return the y location of the front of the OSV when it is vertical
 */
static double LocationManager::getTopY() {
    return getY() + (OSV::LENGTH / 2);
}

/**
 * @return the y location of the back of the OSV when it is vertical
 */
static double LocationManager::getBottomY() {
    return getY() - (OSV::LENGTH / 2);
}

/**
 * Determines the angular heading of the OSV
 * @return the angular heading of the OSV, scaled between 0 and 360 degrees.
 */
static double LocationManager::getHeading() {
  return getHeading(getCurrentLocation().theta);
}

/**
 * Determines the heading of the OSV given a theta value directly from the vision system
 * @param rawThetaVal the heading of the OSV, scaled between -PI and PI radians.
 * @return the angular heading of the OSV, scaled between 0 and 360 degrees.
 */
static double LocationManager::getHeading(double rawThetaValue) {
  return (rawThetaValue >= 0)
    ? radiansToDegrees(rawThetaValue)
    : 360 + radiansToDegrees(rawThetaValue);
}

/**
 * @return the heading of the OSV to the closest 90 degree increment
 */
static double LocationManager::getRoundedHeading() {
  double heading = getHeading();

  if(heading > 45. && heading <= 135.) {
    // If the angle is between 45 and 135, return 90
    return 90.;
  } else if(heading > 135. && heading <= 225.) {
    // If the angle is between 135 and 135, return 180
    return 180.;
  } else if(heading > 225. && heading <= 315.) {
    return 270.;
  } else {
    return 0.;
  }
}

/**
 * ========================
 *   DISTANCE SENSOR INFO
 * ========================
 */
 
/**
 * @return the distance retreived by the left front distance sensor, in meters
 */
static double LocationManager::getFrontLeftDistance() {
    return getDistance(frontLeftSensor);
}

/**
 * @return the distance retreived by the right front distance sensor, in meters
 */
static double LocationManager::getFrontRightDistance() {
    return getDistance(frontRightSensor);
}

static double LocationManager::getDistance(const NewPing& sensor) {
    unsigned int medianTimePerPing = sensor.ping_median(Distance::SAMPLE_NUMBER);
    return sensor.convert_cm(medianTimePerPing);
}

/**
 * @return whether there are obstacles to the right of the robot blocking the path
 * to the right of the robot (assuming the robot is facing along the +Y axis)
 */
static bool LocationManager::obstaclesBlockingTheFront() {
  return obstaclesBlockingTheFrontLeft() || obstaclesBlockingTheFrontRight();
}

/**
 * @return whether there are obstacles to the right of the robot blocking the path
 * to the right of the robot (assuming the robot is facing along the +Y axis)
 */
static bool LocationManager::obstaclesBlockingTheFrontRight() {
  return getFrontRightDistance() < Distance::SAFE_FRONT_DISTANCE;
}

static bool LocationManager::obstaclesBlockingTheFrontLeft() {
  return getFrontLeftDistance() < Distance::SAFE_FRONT_DISTANCE;
}

/**
 * ========================
 *   MISSION LOCATION INFO
 * ========================
 */
static Coordinate* LocationManager::getMissionLocation() {
  if(MISSION_LOCATION == 0) {
    waitForLocationUpdate();
    MISSION_LOCATION = &Enes100.destination;
  }
  return MISSION_LOCATION;
}

// Gives the y-location of the mission site's center
static double LocationManager::getMissionCenterY() {
    return getMissionLocation()->y;
}

// Gives the x-location of the mission site's center
static double LocationManager::getMissionCenterX() {
    return getMissionLocation()->x;
}

// X of the left of the mission
static double LocationManager::getMissionX() {
    return getMissionCenterX() - FireSite::RADIUS;
}

// Y of the top of the mission
static double LocationManager::getMissionY() {
    return getMissionCenterY() + FireSite::RADIUS;
}

// Gives the y-location of the bottom of the mission site
static double LocationManager::getMissionBottomY() {
    return getMissionCenterY() - FireSite::RADIUS;
}

// Gives the y-location of the bottom of the mission site
static double LocationManager::getMissionBackX() {
    return getMissionCenterX() + FireSite::RADIUS;
}
