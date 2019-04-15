#ifndef FLAME_SENSOR
#define FLAME_SENSOR

class FlameSensor {
private:
  const pin dataPin;

  // The raw analog value below which a reading will be considered a flame
  const static int FLAME_DETECTED_THRESHOLD = 35;
  
  // The raw analog value below which a reading will be considered a flame
  const static int CENTER_FLAME_DETECTED_THRESHOLD = 300;
  int getMedianValue(int numberOfSamples = 100, int samplingRate = 100);

public:
  FlameSensor(pin dataPin);
  int getRawValue();
  bool didDetectFlame();
  bool didDetectCenterFlame();
};

#endif
