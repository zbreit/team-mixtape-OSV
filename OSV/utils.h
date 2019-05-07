#ifndef UTILS
#define UTILS

#include <Enes100.h>
#include <math.h>
#include "Constants.h"

/**
 * Contains convenience methods for various math and angle calculations
 */

// Basic Data Structures

/**
 * Stores which obstacle lane the OSV is in. 
 */
enum class Lane
{
    MIDDLE,
    RIGHT,
    LEFT
};

// Helper Methods

/**
 * Prints the following string: "{key}: {value}\n"
 */
template <typename V>
void printPair(String key, V value) {
  // NOTE: This is declared here due to an intricacy with template functions
  // needing be defined and declared in the same file
  Enes100.print(key);
  Enes100.print(": ");
  Enes100.println(value);

  //TODO: remove
  Serial.print(key);
  Serial.print(": ");
  Serial.println(value);
}

/**
 * Returns the distance between two coordinates
 * @param startPoint the first point
 * @param endPoint the second point
 * @return the distance between the two points. If B is behind the vector of A, 
 */
double distanceBetween(Coordinate &startPoint, Coordinate &endPoint);

/**
 * @return if the endPoint is behind the startPoint
 */
bool isBehind(Coordinate &startPoint, Coordinate &endPoint);


/**
 * Returns a new coordinate that extends the given location vector
 * by the distance
 * @param location a vector representing a given position
 * @param distance how far you wish to extend the given vector. If it is positive, the vector
 * extends forward, if it is negative, the vector extends backwards. 
 * @return a coordinate with the advanced location
 */
Coordinate advance(Coordinate &location, double distance);

/**
 * Converts an angle measurment from radians to degrees
 * @param angle the angle in radians
 * @return the angle in degrees
 */
double radiansToDegrees(double angle);

/**
 * Determines how far apart two angles are
 * @param startingAnlge the first angle, in degreees
 * @param endingAngle the second angle, in degreees
 * @return the shortest distance between angle1 and angle2
 */
double getAngularDifference(double startingAngle, double endingAngle);

/**
 * @return the norm of a vector with the given componenets
 */
double norm(double xComponent, double yComponent);


/**
 * @return the absolute value of num
 */
double dabs(double num);

/**
 * Scales the given value in the range [fromLow, fromHigh] to [toLow, toHigh]
 */
float fmap(float value, float fromLow, float fromHigh, float toLow, float toHigh);

/**
 * @return HIGH if the current state is LOW, LOW if the current state is HIGH
 */
int invertState(int state);

// Debugging Methods

/**
 * Prints the points x, y and theta to the serial monitor
 */
void printPoint(Coordinate point, const char* nameOfPoint = "Point");

#endif
