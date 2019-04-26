#include "utils.h"

/**
 * Returns the distance between two coordinates
 * @param startPoint the first point
 * @param endPoint the second point
 * @return the distance between the two points. If B is behind the vector of A, 
 */
double distanceBetween(Coordinate& startPoint, Coordinate& endPoint) {
    // Multiply the distance by -1 if the endpoint is beind the startpoint
    int directionalMultiplier = isBehind(startPoint, endPoint) ? -1 : 1;
    
    return directionalMultiplier * norm(startPoint.x - endPoint.x, startPoint.y - endPoint.y);
}

/**
 * Determine if the vector of the start
 */
bool isBehind(Coordinate& startPoint, Coordinate& endPoint) {
  // Define the component vector for the starting point's orientation
  double startPointX = cos(startPoint.theta);
  double startPointY = sin(startPoint.theta);

  // Now, we find the x and y distance between the endpoint and the start point
  // as the second vector's components
  double endPointX = endPoint.x - startPoint.x;
  double endPointY = endPoint.y - startPoint.y;

  // Now, if the dot product of the two vectors is negative, the endPoint is behind the startPoint
  double dotProduct = (startPointX * endPointX) + (startPointY * endPointY);
  return dotProduct < 0;
}

/**
 * Finds the norm of a vector with the given componenets
 */
double norm(double xComponent, double yComponent) {
  return sqrt(pow(xComponent, 2) + pow(yComponent, 2));
}

/**
 * @return HIGH if the current state is LOW, LOW if the current state is HIGH
 */
int invertState(int state) {
  return (state == HIGH) ? LOW : HIGH;
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
 * Takes the given value within a specified range [fromLow, fromHigh] and remaps it to [toLow, toHigh]
 * @param value the number you want to rescale
 * @param fromLow the lower bound of the original range
 * @param fromHigh the upper bound of the original range
 * @param toLow the lower bound of the new range
 * @param toHigh the upper bound of the new range
 * @return the remapped value in the new range
 */
float fmap(float value, float fromLow, float fromHigh, float toLow, float toHigh) {
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

/**
 * Prints the points x, y and theta to the serial monitor
 */
void printPoint(Coordinate point, String nameOfPoint) {
  Enes100.print(&nameOfPoint);
  Enes100.print(": (");
  Enes100.print(point.x);
  Enes100.print(", ");
  Enes100.print(point.y);
  Enes100.print(", ");
  Enes100.print(point.theta);
  Enes100.println(")");
}
 
