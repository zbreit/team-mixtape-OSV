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
  while(!Enes100Simulation.begin()) {}
  Navigator* navigator = Navigator::getInstance();
//  navigator->navigate();
}

void loop() {
  DriveTrain::getInstance()->drive(1.);
  Serial.print("Right: ");
  Serial.println();
  Serial.print("Front: ");
  Serial.println(Enes100Simulation.readDistanceSensor(1));
  Serial.println();
  delay(2000);
  
}
