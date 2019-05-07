#include "Constants.h"

// INFORMATION TO UPDATE
const int OSV::ARUCO_MARKER_ID = 26;

// WIFI
const pin Pins::WIFI_TRANSMITTER = 5;
const pin Pins::WIFI_RECEIVER = 6;

// Digital Sensors
const pin Pins::LEFT_ULTRASONIC_TRIGGER = 3;
const pin Pins::LEFT_ULTRASONIC_ECHO = 3;
const pin Pins::RIGHT_ULTRASONIC_TRIGGER = 4;
const pin Pins::RIGHT_ULTRASONIC_ECHO = 4;

// Motors
// Right motor connected to M1 on the Romeo, left to M2
const pin Pins::RIGHT_MOTOR_PWM = 10;
const pin Pins::LEFT_MOTOR_PWM = 11;
const pin Pins::RIGHT_MOTOR_DIR1 = 8;
const pin Pins::RIGHT_MOTOR_DIR2 = 9;
const pin Pins::LEFT_MOTOR_DIR1 = 12;
const pin Pins::LEFT_MOTOR_DIR2 = 13;
const pin Pins::ARM_MOTOR = 7;

// Analog Input
const pin Pins::ARM_MOTOR_POS = A0;
const pin Pins::IR_FLAME_SENSOR = A5;

// Distance
const byte Distance::SAMPLE_NUMBER = 11;            // The number of distance measurements to take before returning the median
const double Distance::EQUALITY_THRESHOLD = 0.025;  // The distance, in meters, for when two positions are considered equal
const double Distance::SAFE_FRONT_DISTANCE = 0.3;   // The distance, in meters, for when an obstacle is in the way
const double Distance::ULTRASONIC_MAX_RANGE = 1.;   // The distance, in meters, where it is safe to have an obstacle present
const double Distance::IR_MAX_RANGE = 1.;           // The maximum discernible distance of the IR distance sensor, in meters
const double Distance::REACHED_MISSION_SITE = 0.15; // The maximum difference between the OSV and the mission site positions after avoiding all obstacles

// Angles
const double Angle::EQUALITY_THRESHOLD = 0.25; // The angular difference between 2 angles, in degrees, at which they are considred equal
const double Angle::LANE_SHIFT = radiansToDegrees(atan2(Distance::SAFE_FRONT_DISTANCE +
                                                            OSV::LENGTH / 2,
                                                        Field::OBSTACLE_LANE_WIDTH)); // Angle to shift between the lanes, in degrees
const int Angle::EXTENDED_ARM_ANGLE = 70;
const int Angle::RESTING_ARM_ANGLE = 0;

// OSV Dimensions
const double OSV::LENGTH = 0.265;
const double OSV::WIDTH = 0.32;
const double OSV::ARM_CENTER_OFFSET = 0.0625; // The distance between the center of the OSV and the arm along the length of the OSV
const double OSV::ARM_EXTENSION_LENGTH = 0.085;
const double ARUCO_MARKER_CENTER_OFFSET = 0.; // The distance between the center of the OSV and the center of the Aruco marker along the length of the OSV

// Field Dimensions
const double Field::LENGTH = 4.;
const double Field::WIDTH = 2.;
const double Field::ROCKY_TERRAIN_X = 1.25;
const double Field::OBSTACLE_LANE_WIDTH = (Field::WIDTH - 0.2) / 3.;
const double Field::OBSTACLE_ENDZONE_X = 2.9; // The x location after which there are guaranteed to be no obstacles

// Fire Site Dimensions
const double FireSite::RADIUS = 0.225 / 2;
const double FireSite::EDGE_TO_CANDLE = 0.052;
const double FireSite::CANDLE_TO_CANDLE = 0.12;
const double FireSite::CANDLE_INSET = 0.05;
const int FireSite::SIDE_COUNT = 4;

// PID Constants
const double PIDConstants::TURN_P = 0.05;
const double PIDConstants::DRIVE_P = 4.;
const double PIDConstants::DRIVE_AT_ANGLE_P = 0.05;
const double PIDConstants::COMMAND_TIMEOUT = 10000.;

// Motors
const double Motors::LEFT_MIN_COMMAND = 0.2;  // The lowest left motor speed at which the robot will move
const double Motors::RIGHT_MIN_COMMAND = 0.2; // The lowest right motor speed at which the robot will move
const double Motors::LEFT_MAX_COMMAND = 1.;   // The highest left motor speed
const double Motors::RIGHT_MAX_COMMAND = 1.;  // The highest right motor speed
const bool Motors::LEFT_IS_REVERSED = false;  // Whether the polarity of the motor should be flipped
const bool Motors::RIGHT_IS_REVERSED = false; // Whether the polarity of the motor should be flipped
const int Motors::SERVO_COMMAND_DELAY_MS = 150; // The delay between successive writes to the servo (used to slow down the rotation)
