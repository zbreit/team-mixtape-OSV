#ifndef EXTINGUISHER
#define EXTINGUISHER

#include "utils.h"
#include "FlameSensor.h"

class ExtinguishingArm
{
private:
  Servo armMotor;
  FlameSensor flameSensor;
  int flameCount;
  const int LOW_STATE_ANGLE = 20;
  const int HIGH_STATE_ANGLE = 0;

  /**
   * Lower the arm to the extinguishing position
   */
  void lower();

  /**
   * Raise the arm to the upwards position
   */
  void raise();

public:
  /**
   * Create an extinguishing arm
   * @param armMotorPin the signal pin of the arm servo 
   * @param flameSensorPin the analog input pin of the flame sensor
   */
  ExtinguishingArm(pin armMotorPin, pin flameSensorPin);

  /**
   * If a flame is detected by the arm, extinguish that flame and count it
   */
  void extinguish();

  /**
   * Sends the current flame count to the vision system. 
   * PRECONDITION: Should only be used after counting all flames
   */
  void reportFlameCount();
};

#endif