#ifndef UTILS
#define UTILS
#include <math.h>

// Helper Methods
double distanceBetween(Coordinate& point1, Coordinate& point2);
Coordinate getCurrentLocation();
Coordinate advanceForward(Coordinate& location, double distance);
double radiansToDegrees(double angle);
double getAngularDifference(double startingAngle, double endingAngle);

#endif
