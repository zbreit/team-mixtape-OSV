#ifndef UTILS
#define UTILS
#include <math.h>

// Basic Data Structures
enum class Direction { UP, DOWN };

// Helper Methods
double distanceBetween(Coordinate& startPoint, Coordinate& endPoint);
bool isFacing(Coordinate& startPoint, Coordinate& endPoint);
Coordinate advance(Coordinate& location, double distance);
double radiansToDegrees(double angle);
double getAngularDifference(double startingAngle, double endingAngle);

// Debugging Methods
void printPoint(Coordinate point, String nameOfPoint="Point");

#endif
