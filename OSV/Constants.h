#ifndef CONSTANTS
#define CONSTANTS
#include "utils.h"

typedef unsigned char pin;
typedef unsigned char byte;

/** 
 * Stores all configuration info (e.g., pin mappings, PID constants, OSV dimensions)
 */

namespace Pins
{
// Digital IO
extern const pin LEFT_ULTRASONIC_ECHO;
extern const pin LEFT_ULTRASONIC_TRIGGER;
extern const pin RIGHT_ULTRASONIC_ECHO;
extern const pin RIGHT_ULTRASONIC_TRIGGER;

// Motors
extern const pin RIGHT_MOTOR_PWM;
extern const pin LEFT_MOTOR_PWM;
extern const pin RIGHT_MOTOR_DIR1;
extern const pin RIGHT_MOTOR_DIR2;
extern const pin LEFT_MOTOR_DIR1;
extern const pin LEFT_MOTOR_DIR2;
extern const pin ARM_MOTOR;

// Analog Input
extern const pin IR_FLAME_SENSOR;
extern const pin ARM_MOTOR_POS;

// WIFI
extern const pin WIFI_TRANSMITTER;
extern const pin WIFI_RECEIVER;
} // namespace Pins

namespace Distance
{
// Ultrasonic/Other Distance Information
extern const byte SAMPLE_NUMBER;
extern const double EQUALITY_THRESHOLD;
extern const double OBSTACLE_PRESENT;
extern const double SAFE_FRONT_DISTANCE;
extern const double REACHED_MISSION_SITE;
extern const double ULTRASONIC_MAX_RANGE;
extern const double IR_MAX_RANGE;
} // namespace Distance

namespace Angle
{
// Angle Information
extern const double EQUALITY_THRESHOLD;
extern const double LANE_SHIFT;
extern const int RESTING_ARM_ANGLE;
extern const int EXTENDED_ARM_ANGLE;
} // namespace Angle

namespace OSV
{
// OSV Dimensions
extern const double LENGTH;
extern const double WIDTH;
extern const int ARUCO_MARKER_ID;
extern const double ARM_EXTENSION_LENGTH;
extern const double ARUCO_MARKER_CENTER_OFFSET;
extern const double ARM_CENTER_OFFSET;
} // namespace OSV

namespace Field
{
// Field Dimensions
extern const double LENGTH;
extern const double WIDTH;
extern const double ROCKY_TERRAIN_X;
extern const double OBSTACLE_LANE_WIDTH;
extern const double OBSTACLE_ENDZONE_X;
} // namespace Field

namespace FireSite
{
// Fire Site Dimensions
extern const double RADIUS;
extern const double EDGE_TO_CANDLE;
extern const double CANDLE_TO_CANDLE;
extern const double CANDLE_INSET;
extern const int SIDE_COUNT;
} // namespace FireSite

namespace PIDConstants
{
extern const double TURN_P; // Proportionality constant for turning
extern const double DRIVE_P;
extern const double DRIVE_AT_ANGLE_P; // Proportionality constant for determining angular adjustments on each side
extern const double COMMAND_TIMEOUT;  // The maximum duration of a given command in ms
} // namespace PIDConstants

namespace Motors
{
extern const double LEFT_MIN_COMMAND;
extern const double RIGHT_MIN_COMMAND;
extern const double LEFT_MAX_COMMAND;
extern const double RIGHT_MAX_COMMAND;
extern const bool LEFT_IS_REVERSED;
extern const bool RIGHT_IS_REVERSED;
extern const int SERVO_COMMAND_DELAY_MS;
} // namespace Motors

#endif
