#ifndef CONSTANTS
#define CONSTANTS

typedef unsigned char pin;

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
}

namespace OSV {
    // OSV Dimensions
    extern const double LENGTH;
    extern const double WIDTH;
}

namespace Field {
    // Field Dimensions
    extern const double LENGTH;
    extern const double WIDTH;
}

namespace FireSite {
    // Fire Site Dimensions
    extern const double LENGTH;
    extern const double WIDTH;
}

#endif
