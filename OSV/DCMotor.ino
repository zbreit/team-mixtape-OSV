#include "DCMotor.h"

DCMotor::DCMotor(pin directionPin1, pin directionPin2, pin speedPin, double speedFloor, double speedCap, bool isReversed) : directionPin1(directionPin1),
                                                                                                                            directionPin2(directionPin2),
                                                                                                                            speedPin(speedPin),
                                                                                                                            speedFloor(speedFloor),
                                                                                                                            speedCap(speedCap),
                                                                                                                            isReversed(isReversed)
{
  pinMode(speedPin, OUTPUT);
  pinMode(directionPin1, OUTPUT);
  pinMode(directionPin2, OUTPUT);
}


void DCMotor::setDirection(double speed)
{
  // Turn on the direction pin if the motor is driving forward, and set it to 0 otherwise
  int direction = (speed > 0.0) ? HIGH : LOW;
  direction = isReversed ? invertState(direction) : direction; // If the motor should be reversed, swap the direction

  // On the LM298N, if pin1 is LOW & pin2 is HIGH, it will drive forwards
  digitalWrite(directionPin1, direction);
  digitalWrite(directionPin2, invertState(direction));
}


void DCMotor::set(double speed)
{
  setDirection(speed);
  // Map the speed to something between speedFloor and speedCap
  speed = dabs(speed);
  speed = fmap(speed, 0., 1., speedFloor, speedCap);
  speed = constrain(speed, speedFloor, speedCap);
  speed *= 255;

  // Set the speed of the motor
  analogWrite(speedPin, speed);
}

void DCMotor::stop()
{
  // On the LM298N, setting both direction pins to the same value stops the motor
  digitalWrite(directionPin1, LOW);
  digitalWrite(directionPin2, LOW);
}
