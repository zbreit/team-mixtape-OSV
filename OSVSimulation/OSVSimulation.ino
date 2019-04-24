#include <ArduinoSTL.h>
#include <NewPing.h>
#include <Servo.h>
#include <Enes100Simulation.h>
#include <TankSimulation.h>

#include "Constants.h"
#include "utils.h"
#include "FlameSensor.h"
#include "DriveTrain.h"
#include "DCMotor.h"
#include "LocationManager.h"
#include "ExtinguishingArm.h"
#include "Navigator.h"

void setup() {
	TankSimulation.begin();
  while(!Enes100Simulation.begin()) {}
  Navigator* navigator = Navigator::getInstance();
  navigator->navigate();
  navigator->countAndExtinguishFlames();
}

void loop() {
  
}
