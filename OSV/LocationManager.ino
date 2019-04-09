/**
 * =======================
 *   STATIC MEMBER SETUP
 * =======================
 */
const NewPing LocationManager::sideDistanceSensor(Pins::ULTRASONIC, Pins::ULTRASONIC);
const SharpDistSensor LocationManager::frontDistanceSensor(Pins::IR_DISTANCE, Distance::SAMPLE_NUMBER);
const Coordinate* LocationManager::MISSION_LOCATION = &getMissionLocation();

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
 * @return the y location of the front of the OSV whe it is vertical
 */
static double LocationManager::getFrontY() {
    return getY() + (OSV::LENGTH / 2);
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
 * @return the distance retreived by the side distance sensor, in meters
 */
static double LocationManager::getFrontDistance() {
    frontDistanceSensor.setModel(SharpDistSensor::GP2Y0A41SK0F_5V_DS);
    return frontDistanceSensor.getDist() / 1000.;
}

/**
 * @return the distance retreived by the side distance sensor, in meters
 */
static double LocationManager::getSideDistance() {
    unsigned int medianTimePerPing = sideDistanceSensor.ping_median(Distance::SAMPLE_NUMBER);
    return sideDistanceSensor.convert_cm(medianTimePerPing);
}

/**
 * @return whether there are obstacles to the right of the robot blocking the path
 * to the right of the robot (assuming the robot is facing along the +Y axis)
 */
static bool LocationManager::obstaclesAreBlockingTheRight() {
  return (getMissionX() - getSideX() + Distance::THRESHOLD) > getSideDistance();
}

static bool LocationManager::obstaclesAreBlockingTheFront(double distanceToMissionSite) {
  return distanceToMissionSite + Distance::THRESHOLD > getFrontDistance();
}

/**
 * ========================
 *   MISSION LOCATION INFO
 * ========================
 */
static Coordinate LocationManager::getMissionLocation() {
  waitForLocationUpdate();
  return Enes100.destination;
}

static double LocationManager::getMissionY() {
    Serial.print("MISSION LOCATION Y: ");
    Serial.println(MISSION_LOCATION->y);
    return MISSION_LOCATION->y;
}

static double LocationManager::getMissionX() {
    return MISSION_LOCATION->x;
}

// Gives the x-location of the mission site's center
static double LocationManager::getMissionCenterX() {
    return getMissionX() + FireSite::RADIUS;
}

// Gives the y-location of the mission site's center
static double LocationManager::getMissionCenterY() {
    return getMissionY() - FireSite::RADIUS;
}

// Gives the y-location of the bottom of the mission site
static double LocationManager::getMissionBottomY() {
    return getMissionY() - 2 * FireSite::RADIUS;
}

// Gives the y-location of the bottom of the mission site
static double LocationManager::getMissionBackX() {
    return getMissionY() + 2 * FireSite::RADIUS;
}
