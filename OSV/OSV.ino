#include <MedianFilter.h>
#include <SharpDistSensor.h>

#include <NewPing.h>
#include <Servo.h>
#include <Enes100.h>

#include "Constants.h"
#include "utils.h"
#include "FlameSensor.h"
#include "DriveTrain.h"
#include "DCMotor.h"
#include "LocationManager.h"
#include "Navigator.h"

void setup() {
  while(!Enes100.begin("MIXTAPE", FIRE, OSV::ARUCO_MARKER_ID, Pins::WIFI_RECEIVER, Pins::WIFI_TRANSMITTER)) {}
  Navigator* navigator = Navigator::getInstance();
  navigator->navigate();
  delay(2000);
}

void loop() {
  
}
