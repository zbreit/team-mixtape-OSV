#include "ExtinguishingArm.h"

ExtinguishingArm::ExtinguishingArm(pin armMotorPin, pin flameSensorPin) : armMotor(),
                                                                          flameSensor(flameSensorPin),
                                                                          flameCount(0)
{
  pinMode(armMotorPin, OUTPUT);
  armMotor.attach(armMotorPin);
}

void ExtinguishingArm::extinguish()
{
  if (flameSensor.didDetectFlame())
  {
    Enes100.println("Detected Flame");
    lower();
    delay(5000); // TODO: Delay 5 seconds (CHANGE THIS IF UNRELIABLE)
    raise();
    flameCount++;
    Enes100.print("Extinguished Flame ");
    Enes100.println(flameCount);
  }
}

void ExtinguishingArm::reportFlameCount()
{
  Enes100.mission(flameCount);
}

void ExtinguishingArm::lower()
{
  armMotor.write(LOW_STATE_ANGLE);
}

void ExtinguishingArm::raise()
{
  armMotor.write(HIGH_STATE_ANGLE);
}
