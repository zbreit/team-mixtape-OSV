#ifndef FLAME_SENSOR
#define FLAME_SENSOR

class FlameSensor {
private:
  const pin dataPin;

  // The raw analog value below which a reading will be considered a flame
  const static int FLAME_DETECTED_THRESHOLD = 35;

public:
  FlameSensor(pin dataPin);
  int getRawValue();
  bool detectFlame(int numberOfSamples = 100, int samplingRate = 100);
};

#endif
