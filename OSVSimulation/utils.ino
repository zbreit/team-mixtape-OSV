/**
 * Returns the distance between two coordinates
 * @param startPoint the first point
 * @param endPoint the second point
 * @return the distance between the two points. If B is behind the vector of A, 
 */
double distanceBetween(Coordinate& startPoint, Coordinate& endPoint) {
    // Multiply the distance by -1 if the endpoint is beind the startpoint
    int directionalMultiplier = isFacing(startPoint, endPoint) ? 1 : -1;
    
    return directionalMultiplier * sqrt(pow(startPoint.x - endPoint.x, 2) + pow(startPoint.y - endPoint.y, 2));
}

/**
 * Determine if the vector of the start
 */
bool isFacing(Coordinate& startPoint, Coordinate& endPoint) {
  // Define the component vector for the starting point's orientation
  double startPointX = cos(startPoint.theta);
  double startPointY = sin(startPoint.theta);

  // Now, we find the x and y distance between the endpoint and the start point
  // as the second vector's components
  double endPointX = endPoint.x - startPoint.x;
  double endPointY = endPoint.y - startPoint.y;

  // Now, if the dot product of 
  double dotProduct = (startPointX * endPointX) + (startPointY + endPointY);
  Serial.print("Dot product is: ");// TODO: remove
  Serial.println(dotProduct);
  return dotProduct > 0;
}

/**
 * Returns a new coordinate that extends the given location vector
 * by the distance
 * @param location a vector representing a given position
 * @param distance how far you wish to extend the given vector. Must be positive.
 * @return a coordinate with the advanced location
 */
Coordinate advance(Coordinate& location, double distance) {
  double xOffset = distance * cos(location.theta);
  double yOffset = distance * sin(location.theta);
  return Coordinate(location.x + xOffset, location.y + yOffset);
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

/**
 * Prints the points x, y and theta to the serial monitor
 */
void printPoint(Coordinate point, String nameOfPoint) {
  Serial.print(nameOfPoint);
  Serial.print(": (");
  Serial.print(point.x);
  Serial.print(", ");
  Serial.print(point.y);
  Serial.print(", ");
  Serial.print(point.theta);
  Serial.println(")");
}
 
