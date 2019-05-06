#include "ExtinguishingArm.h"

ExtinguishingArm::ExtinguishingArm(pin armMotorPin, pin flameSensorPin) : armMotor(),
                                                                          flameSensor(flameSensorPin),
                                                                          flameCount(0)
{
  pinMode(armMotorPin, OUTPUT);
  armMotor.write(0); // 0 the servo before attaching it
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
  for(int currentAngle = armMotor.read(); currentAngle < LOW_STATE_ANGLE; currentAngle++) {
    armMotor.write(currentAngle);
    delay(Motors::SERVO_COMMAND_DELAY_MS);
  }
}

void ExtinguishingArm::raise()
{
  for(int currentAngle = armMotor.read(); currentAngle > HIGH_STATE_ANGLE; currentAngle--) {
    armMotor.write(currentAngle);
    delay(Motors::SERVO_COMMAND_DELAY_MS);
  }
}
