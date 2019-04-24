#include <ArduinoSTL.h>
#include <NewPing.h>
#include <Servo.h>
#include <Enes100.h>

#include "Constants.h"
#include "utils.h"
#include "FlameSensor.h"
#include "DriveTrain.h"
#include "DCMotor.h"
#include "LocationManager.h"
#include "ExtinguishingArm.h"
#include "Navigator.h"

void setup() {
  while(!Enes100.begin("MIXTAPE", FIRE, OSV::ARUCO_MARKER_ID, Pins::WIFI_RECEIVER, Pins::WIFI_TRANSMITTER)) {
    Enes100.println("Connecting to vision system...");
  }
  Enes100.println("Connected!!!");
  Navigator* navigator = Navigator::getInstance();
  navigator->navigate();
  navigator->countAndExtinguishFlames();
}

void loop() {
  
}
