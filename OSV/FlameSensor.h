#ifndef FLAME_SENSOR
#define FLAME_SENSOR

#include "utils.h"

class FlameSensor
{
private:
  const pin dataPin;

  // The raw analog value below which a reading will be considered a flame
  const static int FLAME_DETECTED_THRESHOLD = 35;

  // The raw analog value below which a reading will be considered a flame
  const static int CENTER_FLAME_DETECTED_THRESHOLD = 300;

  /**
   * Get the median sensor value for a given number of smaples
   * @param numberOfSamples the number of samples to take before making the determination
   * @param samplingRate the number of samples to be taken per second
   */
  int getMedianValue(int numberOfSamples = 100, int samplingRate = 100);

public:
  /**
   * Creates a flame sensor
   * @param dataPin the analog pin to which the sensor is physically connected
   */
  FlameSensor(pin dataPin);

  /**
   * @return the raw analog reading from the sensor's pin
   */
  int getRawValue();

  /**
   * Determine whether or not a flame is currently in front of the sensor.
   */
  bool didDetectFlame();

  /**
 * Determine whether or not the center flame is active.
 * PRECONDITION: assumes all flames were previously cleared before this function is called
 */
  bool didDetectCenterFlame();
};

#endif
