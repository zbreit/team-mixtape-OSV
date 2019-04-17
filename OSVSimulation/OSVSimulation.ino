#include <ArduinoSTL.h>

#include <MedianFilter.h>
#include <SharpDistSensor.h>

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
#include "Navigator.h"
#include "ExtinguishingArm.h"

void setup() {
	TankSimulation.begin();
  while(!Enes100Simulation.begin()) {}
  Navigator* navigator = Navigator::getInstance();
  navigator->navigate();
  delay(2000);
}

void loop() {
  
}
