// Digital Sensors
const byte Pins::LEFT_ULTRASONIC_TRIGGER = 8;
const byte Pins::LEFT_ULTRASONIC_ECHO = 8;
const byte Pins::RIGHT_ULTRASONIC_TRIGGER = 9;
const byte Pins::RIGHT_ULTRASONIC_ECHO = 9;

// Motors
const pin Pins::RIGHT_MOTOR_PWM = 5;
const pin Pins::LEFT_MOTOR_PWM = 6;
const pin Pins::RIGHT_MOTOR_DIR = 4;
const pin Pins::LEFT_MOTOR_DIR = 7;
const pin Pins::ARM_MOTOR = 3;

// WIFI
const pin Pins::WIFI_TRANSMITTER = 8;
const pin Pins::WIFI_RECEIVER = 9;

// Distance
const byte Distance::SAMPLE_NUMBER = 11;
const double Distance::THRESHOLD = 0.025;
const double Distance::SAFE_FRONT_DISTANCE = 0.3;
const double Distance::ULTRASONIC_MAX_RANGE = 1.;
const double Distance::IR_MAX_RANGE = 1.; // The maximum discernible distance of the IR distance sensor, in meters
const double Distance::REACHED_MISSION_SITE = 0.15;

// Analog Input
const pin Pins::ARM_MOTOR_POS = A0;
const pin Pins::IR_FLAME_SENSOR = A2;

// OSV Dimensions
const double OSV::LENGTH = 0.299; // TODO: Change back to 0.3 for real OSV
const double OSV::WIDTH = 0.168;
const int OSV::ARUCO_MARKER_ID = 3; // TODO: update
const double OSV::ARM_EXTENSION_LENGTH = 0.15; // TODO: update

// Field Dimensions
const double Field::LENGTH = 4.;
const double Field::WIDTH = 2.;
const double Field::ROCKY_TERRAIN_X = 1.25;
const double Field::OBSTACLE_LANE_WIDTH = (Field::WIDTH - 0.2) / 3.;
const double Field::OBSTACLE_ENDZONE_X = 2.9; // The x location after which there are guaranteed to be no obstacles

// Fire Site Dimensions
const double FireSite::RADIUS = 0.15 / 2; // TODO: change back to 0.225
const double FireSite::EDGE_TO_CANDLE = 0.052;
const double FireSite::CANDLE_TO_CANDLE = 0.12;
const double FireSite::CANDLE_INSET = 0.05;
const int FireSite::SIDE_COUNT = 4;

// PID Constants
const double PIDConstants::TURN_P = 0.05;
const double PIDConstants::DRIVE_P = 4.;
const double PIDConstants::DRIVE_AT_ANGLE_P = 0.05;

// Motors
const double Motors::LEFT_MIN_COMMAND = 0.2;
const double Motors::RIGHT_MIN_COMMAND = 0.2;
const double Motors::LEFT_MAX_COMMAND = 1.;
const double Motors::RIGHT_MAX_COMMAND = 1.;
const bool Motors::LEFT_IS_REVERSED = false;
const bool Motors::RIGHT_IS_REVERSED = false;
