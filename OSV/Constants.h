#ifndef CONSTANTS
#define CONSTANTS

typedef unsigned char pin;
typedef unsigned char byte;

namespace Pins {
    // Digital IO
    extern const pin ULTRASONIC;

    // Motors
    extern const pin RIGHT_MOTOR_PWM;
    extern const pin LEFT_MOTOR_PWM;
    extern const pin RIGHT_MOTOR_DIR;
    extern const pin LEFT_MOTOR_DIR;
    extern const pin ARM_MOTOR;
    
    // Analog Input
    extern const pin IR_FLAME_SENSOR;
    extern const pin ARM_MOTOR_POS;
    extern const pin IR_DISTANCE;

    // WIFI
    extern const pin WIFI_TRANSMITTER;
    extern const pin WIFI_RECEIVER;
}

namespace Distance {
  extern const byte SAMPLE_NUMBER; // The number of distance measurements to take before returning the median
  extern const double THRESHOLD; // The distance, in meters, for when two positions are considered equal
}

namespace OSV {
    // OSV Dimensions
    extern const double LENGTH;
    extern const double WIDTH;
    extern const int ARUCO_MARKER_ID;
}

namespace Field {
    // Field Dimensions
    extern const double LENGTH;
    extern const double WIDTH;
    extern const double ROCKY_TERRAIN_X;
}

namespace FireSite {
    // Fire Site Dimensions
    extern const double RADIUS;
}

namespace PIDConstants {
    extern const double TURN_P; // Proportionality constant for turning
    extern const double DRIVE_P;
}

#endif
