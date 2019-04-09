class ExtinguishingArm {
private:
  Servo armMotor;
  FlameSensor flameSensor;
public:
  /**
   * Create an extinguishing arm
   * @param armMotorPin the signal pin of the arm servo 
   * @param flameSensorPin the analog input pin of the flame sensor
   */
   ExtinguishingArm(pin armMotorPin, pin flameSensorPin);
};
