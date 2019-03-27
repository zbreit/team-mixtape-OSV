typedef unsigned char byte;

namespace Pins {
    // Digital IO
    const byte ULTRASONIC = 8;
    const byte INFRARED_DISTANCE = 10;

    // Motors
    const byte RIGHT_MOTOR_PWM = 5;
    const byte LEFT_MOTOR_PWM = 6;
    const byte RIGHT_MOTOR_DIR = 4;
    const byte LEFT_MOTOR_DIR = 7;
    const byte ARM_MOTOR = 3;
    
    // Analog Input
    const byte FLAME_SENSOR = A4; // Actually A11, but swapped to A4 to test on the UNO
    const byte ARM_MOTOR_POS = A0;
}

namespace OSV {
    // OSV Dimensions
    const double LENGTH = 30.;
    const double WIDTH = 25.;
}

namespace Field {
    // Field Dimensions
    const double LENGTH = 4.;
    const double WIDTH = 2.;
}

namespace FireSite {
    // Fire Site Dimensions
    const double LENGTH = 0.23;
    const double WIDTH = 0.23;
}
