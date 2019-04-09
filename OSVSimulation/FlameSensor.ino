/**
 * Creates a flame sensor
 * @param dataPin the analog pin to which the sensor is physically connected
 */
FlameSensor::FlameSensor(pin dataPin) :
  dataPin(dataPin)
{}

/**
 * @return the raw analog reading from the sensor's pin
 */
int FlameSensor::getRawValue() {
  return analogRead(dataPin);
}


/**
 * Determine whether or not a flame is currently in front of the sensor.
 * @param numberOfSamples the number of samples to take before making the determination
 * @param samplingRate the number of samples to be taken per second
 */
bool FlameSensor::detectFlame(int numberOfSamples, int samplingRate) {
  //TODO: Implement!!
  return getRawValue() < FLAME_DETECTED_THRESHOLD;
}
