#include "Constants.h"

// INFORMATION TO UPDATE
const pin Pins::WIFI_TRANSMITTER = 6;
const pin Pins::WIFI_RECEIVER = 5;
const int OSV::ARUCO_MARKER_ID = 3;

// Digital Sensors
const pin Pins::LEFT_ULTRASONIC_TRIGGER = 8;
const pin Pins::LEFT_ULTRASONIC_ECHO = 8;
const pin Pins::RIGHT_ULTRASONIC_TRIGGER = 9;
const pin Pins::RIGHT_ULTRASONIC_ECHO = 9;

// Motors
// Right motor connected to M1 on the Romeo, left to M2
const pin Pins::RIGHT_MOTOR_PWM = 12;
const pin Pins::LEFT_MOTOR_PWM = 13;
const pin Pins::RIGHT_MOTOR_DIR = 4;
const pin Pins::LEFT_MOTOR_DIR = 7;
const pin Pins::ARM_MOTOR = 3;

// Analog Input
const pin Pins::ARM_MOTOR_POS = A0;
const pin Pins::IR_FLAME_SENSOR = A2;

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

// OSV Dimensions
const double OSV::LENGTH = 0.299; // TODO: Change back to 0.3 for real OSV
const double OSV::WIDTH = 0.168;
const double OSV::ARM_EXTENSION_LENGTH = 0.15; // TODO: update

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
const double PIDConstants::COMMAND_TIMEOUT = 10.;

// Motors
const double Motors::LEFT_MIN_COMMAND = 0.2;  // The lowest left motor speed at which the robot will move
const double Motors::RIGHT_MIN_COMMAND = 0.2; // The lowest right motor speed at which the robot will move
const double Motors::LEFT_MAX_COMMAND = 1.;   // The highest left motor speed
const double Motors::RIGHT_MAX_COMMAND = 1.;  // The highest right motor speed
const bool Motors::LEFT_IS_REVERSED = false;  // Whether the polarity of the motor should be flipped
const bool Motors::RIGHT_IS_REVERSED = false; // Whether the polarity of the motor should be flipped
