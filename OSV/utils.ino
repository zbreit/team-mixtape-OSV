/**
 * Returns the distance between two coordinates
 * @param point1 the first point
 * @param point2 the second point
 * @return the distance between the two points
 */
double distanceBetween(Coordinate& point1, Coordinate& point2) {
    return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}

/**
 * Returns a new coordinate that extends the given location vector
 * by the distance
 * @param location a vector representing a given position
 * @param distance how far you wish to extend the given vector. Must be positive.
 * @return a coordinate with the advanced location
 */
Coordinate advanceForward(Coordinate& location, double distance) {
  double xOffset = distance * cos(location.theta);
  double yOffset = distance * sin(location.theta);

  return Coordinate(location.x + xOffset, location.y + yOffset, location.theta);
}

/**
 * Converts an angle measurment from radians to degrees
 * @param angle the angle in radians
 * @return the angle in degrees
 */
double radiansToDegrees(double angle) {
  return angle / PI * 180.;
}

/**
 * Determines how far apart two angles are
 * @param startingAnlge the first angle, in degreees
 * @param endingAngle the second angle, in degreees
 * @return the shortest distance between angle1 and angle2
 */
double getAngularDifference(double startingAngle, double endAngle) {
  double difference = endAngle - startingAngle;
  if(abs(difference) <= 180) {
    return difference;
  }

  if(difference > 0) {
    return difference - 360.;
  } else {
    return difference + 360.;
  }
}
