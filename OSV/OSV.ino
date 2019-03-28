#include <Servo.h>
#include <Enes100.h>

#include "Constants.h"
#include "FlameSensor.h"
#include "DriveTrain.h"
#include "DCMotor.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Flame Sensor: ");
  Serial.println(Pins::IR_FLAME_SENSOR);
}
