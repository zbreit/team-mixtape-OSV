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

void setup() {
	TankSimulation.begin();
  Serial.begin(9600);
  Enes100Simulation.begin();
  Navigator* navigator = Navigator::getInstance();
  navigator->navigate();
  delay(2000);
}

void loop() {
  Serial.print("FRONT: ");
  Serial.println(Enes100Simulation.readDistanceSensor(1));
  Serial.print("SIDE: ");
  Serial.println(Enes100Simulation.readDistanceSensor(4));
}
