#ifndef FLAME_SENSOR
#define FLAME_SENSOR

class FlameSensor {
private:
  const byte dataPin;

   // The raw analog value below which a reading will be considered a flame
  const static int FLAME_DETECTED_THRESHOLD = 35;

public:
  /**
   * Creates a flame sensor
   * @param dataPin the analog pin to which the sensor is physically connected
   */
  FlameSensor(byte dataPin);

  /**
   * @return the raw analog reading from the sensor's pin
   */
  int getRawValue();

  /**
   * Determine whether or not a flame is currently in front of the sensor.
   * @param numberOfSamples the number of samples to take before making the determination
   * @param samplingRate the number of samples to be taken per second
   */
  bool detectFlame(int numberOfSamples = 100, int samplingRate = 100);
};

#endif
