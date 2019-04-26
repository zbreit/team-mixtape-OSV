#include "FlameSensor.h"

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
 */
bool FlameSensor::didDetectFlame() {
  return getMedianValue() < FLAME_DETECTED_THRESHOLD;
}

/**
 * Determine whether or not the center flame is active.
 * PRECONDITION: assumes all flames were previously cleared before this function is called
 */
bool FlameSensor::didDetectCenterFlame() {
  return getMedianValue() < CENTER_FLAME_DETECTED_THRESHOLD;
}

/**
 * Get the median sensor value for a given number of smaples
 * @param numberOfSamples the number of samples to take before making the determination
 * @param samplingRate the number of samples to be taken per second
 */
int FlameSensor::getMedianValue(int numberOfSamples, int samplingRate) {
  // Collect the given number of samples, and store them in the samples object
  std::vector<int> samples;
  for(int sampleCount = 0; sampleCount < numberOfSamples; sampleCount++) {
    samples.push_back(getRawValue());
    delay(1. / samplingRate * 1000.);
  }
  
  // Return the median value from the samples 
  std::sort(samples.begin(), samples.end());
  return samples.at(samples.size() / 2);
}
