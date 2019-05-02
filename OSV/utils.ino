#include "utils.h"

double distanceBetween(Coordinate &startPoint, Coordinate &endPoint)
{
  // Multiply the distance by -1 if the endpoint is beind the startpoint
  int directionalMultiplier = isBehind(startPoint, endPoint) ? -1 : 1;

  return directionalMultiplier * norm(startPoint.x - endPoint.x, startPoint.y - endPoint.y);
}


bool isBehind(Coordinate &startVector, Coordinate &endPoint)
{
  // Define the component vector for the starting point's orientation
  double startVectorX = cos(startVector.theta);
  double startVectorY = sin(startVector.theta);

  // Now, we find the x and y distance between the endpoint and the start point
  // as the second vector's components
  double endPointX = endPoint.x - startVector.x;
  double endPointY = endPoint.y - startVector.y;

  // Now, if the dot product of the two vectors is negative, the endPoint is behind the startVector
  double dotProduct = (startVectorX * endPointX) + (startVectorY * endPointY);
  return dotProduct < 0;
}


double norm(double xComponent, double yComponent)
{
  return sqrt(pow(xComponent, 2) + pow(yComponent, 2));
}


int invertState(int state)
{
  return (state == HIGH) ? LOW : HIGH;
}


Coordinate advance(Coordinate &location, double distance)
{
  double xOffset = distance * cos(location.theta);
  double yOffset = distance * sin(location.theta);
  return Coordinate(location.x + xOffset, location.y + yOffset);
}


double radiansToDegrees(double angle)
{
  return angle / PI * 180.;
}


double getAngularDifference(double startingAngle, double endAngle)
{
  double difference = endAngle - startingAngle;
  if (dabs(difference) <= 180)
  {
    return difference;
  }

  if (difference > 0)
  {
    return difference - 360.;
  }
  else
  {
    return difference + 360.;
  }
}


float fmap(float value, float fromLow, float fromHigh, float toLow, float toHigh)
{
  return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}


double dabs(double num)
{
  return (num >= 0) ? num : -num;
}


void printPoint(Coordinate point, String nameOfPoint)
{
  Enes100.print(&nameOfPoint);
  Enes100.print(": (");
  Enes100.print(point.x);
  Enes100.print(", ");
  Enes100.print(point.y);
  Enes100.print(", ");
  Enes100.print(point.theta);
  Enes100.println(")");
}
