// Digital Sensors
const byte Pins::ULTRASONIC = 8;

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
const pin Pins::IR_DISTANCE = A1;
const pin Pins::IR_FLAME_SENSOR = A2;

// OSV Dimensions
const double OSV::LENGTH = 0.299; // TODO: Change back to 0.3 for real OSV
const double OSV::WIDTH = 0.168;
const int OSV::ARUCO_MARKER_ID = 3;

// Field Dimensions
const double Field::LENGTH = 4.;
const double Field::WIDTH = 2.;
const double Field::ROCKY_TERRAIN_X = 1.25;
const double Field::OBSTACLE_LANE_WIDTH = (Field::WIDTH - 0.2) / 3.;
const double Field::OBSTACLE_ENDZONE_X = 2.9; // The x location after which there are guaranteed to be no obstacles

// Fire Site Dimensions
const double FireSite::RADIUS = 0.15 / 2; // TODO: change back to 0.225

// PID Constants
const double PIDConstants::TURN_P = 0.05;
const double PIDConstants::DRIVE_P = 4.;
