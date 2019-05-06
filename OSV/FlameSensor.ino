#include "FlameSensor.h"

FlameSensor::FlameSensor(pin dataPin) : dataPin(dataPin)
{
  pinMode(dataPin, INPUT);
}


int FlameSensor::getRawValue()
{
  return analogRead(dataPin);
}

bool FlameSensor::didDetectFlame()
{
  return getMedianValue() < FLAME_DETECTED_THRESHOLD;
}

bool FlameSensor::didDetectCenterFlame()
{
  return getMedianValue() < CENTER_FLAME_DETECTED_THRESHOLD;
}


int FlameSensor::getMedianValue(int numberOfSamples, int samplingRate)
{
  // Collect the given number of samples, and store them in the samples object
  std::vector<int> samples;
  for (int sampleCount = 0; sampleCount < numberOfSamples; sampleCount++)
  {
    samples.push_back(getRawValue());
    delay(1. / samplingRate * 1000.);
  }

  // Return the median value from the samples
  std::sort(samples.begin(), samples.end());
  return samples.at(samples.size() / 2);
}
