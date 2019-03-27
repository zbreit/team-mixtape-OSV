#include "subsystems.h"

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.print("Flame Sensor: ");
  Serial.println(Pins::FLAME_SENSOR);
}
