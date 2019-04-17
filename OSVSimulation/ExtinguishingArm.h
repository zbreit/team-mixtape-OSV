class ExtinguishingArm {
private:
  Servo armMotor;
  FlameSensor flameSensor;
  int flameCount;
  const int LOW_STATE_ANGLE = 20;
  const int HIGH_STATE_ANGLE = 0;
  void lower();
  void raise();
public:
   ExtinguishingArm(pin armMotorPin, pin flameSensorPin);
   void extinguish();
   void handleCurrentFlame();
};
