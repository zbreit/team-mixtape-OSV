/**
 * =======================
 *   STATIC MEMBER SETUP
 * =======================
 */
const NewPing LocationManager::frontRightSensor(Pins::ULTRASONIC, Pins::ULTRASONIC);
const SharpDistSensor LocationManager::frontLeftSensor(Pins::IR_DISTANCE, Distance::SAMPLE_NUMBER);
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
  double theta = getCurrentLocation().theta;
  return (theta >= 0)
    ? radiansToDegrees(theta)
    : 360 + radiansToDegrees(theta);
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
    frontLeftSensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);
    return frontLeftSensor.getDist() / 1000.;
}

/**
 * @return the distance retreived by the right front distance sensor, in meters
 */
static double LocationManager::getFrontRightDistance() {
    unsigned int medianTimePerPing = frontRightSensor.ping_median(Distance::SAMPLE_NUMBER);
    return frontRightSensor.convert_cm(medianTimePerPing);
}

/**
 * @return whether there are obstacles to the right of the robot blocking the path
 * to the right of the robot (assuming the robot is facing along the +Y axis)
 */
static bool LocationManager::obstaclesBlockingTheFront() {
  //TODO: replace LocationManager::getSideDistance() with getSideDistance();
  return obstaclesBlockingTheFrontLeft() || obstaclesBlockingTheFrontRight();
}

/**
 * @return whether there are obstacles to the right of the robot blocking the path
 * to the right of the robot (assuming the robot is facing along the +Y axis)
 */
static bool LocationManager::obstaclesBlockingTheFrontRight() {
  //TODO: replace LocationManager::getSideDistance() with getSideDistance();
  return LocationManager::getFrontRightDistance() < Distance::SAFE_FRONT_DISTANCE;
}

static bool LocationManager::obstaclesBlockingTheFrontLeft() {
  //TODO: replace LocationManager::getFrontDistance() with getFrontDistance();
  return LocationManager::getFrontLeftDistance() < Distance::SAFE_FRONT_DISTANCE;
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
