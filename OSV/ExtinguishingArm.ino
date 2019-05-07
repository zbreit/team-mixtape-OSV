#include "ExtinguishingArm.h"

ExtinguishingArm::ExtinguishingArm(pin armMotorPin, pin flameSensorPin) : armMotor(),
                                                                          flameSensor(flameSensorPin),
                                                                          armMotorPin(armMotorPin),
                                                                          flameCount(0)
{
}


void ExtinguishingArm::init() {
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
  for(int currentAngle = Angle::RESTING_ARM_ANGLE; currentAngle < Angle::EXTENDED_ARM_ANGLE; currentAngle++) {
    Serial.print("\tLowering to ");
    Serial.println(currentAngle);
    armMotor.write(currentAngle);
    delay(Motors::SERVO_COMMAND_DELAY_MS);
  }
}

void ExtinguishingArm::raise()
{
  for(int currentAngle = Angle::EXTENDED_ARM_ANGLE; currentAngle > Angle::RESTING_ARM_ANGLE; currentAngle--) {
    armMotor.write(currentAngle);
    delay(Motors::SERVO_COMMAND_DELAY_MS);
  }
}
