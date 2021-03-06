#ifndef UTILS
#define UTILS
#include <math.h>

// Basic Data Structures
enum class Direction { UP, DOWN };
enum class Lane { MIDDLE, RIGHT, LEFT };

// Helper Methods
double distanceBetween(Coordinate& startPoint, Coordinate& endPoint);
bool isBehind(Coordinate& startPoint, Coordinate& endPoint);
Coordinate advance(Coordinate& location, double distance);
double radiansToDegrees(double angle);
double getAngularDifference(double startingAngle, double endingAngle);
double norm(double xComponent, double yComponent);
float fmap(float value, float fromLow, float fromHigh, float toLow, float toHigh);
void sendFlameCount(int numberOfFlames);
int invertState(int state);

// Debugging Methods
void printPoint(Coordinate point, String nameOfPoint="Point");

#endif
