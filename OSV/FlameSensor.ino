FlameSensor::FlameSensor(byte dataPin) :
  dataPin(dataPin)
{}

int FlameSensor::getRawValue() {
  return analogRead(dataPin);
}

bool FlameSensor::detectFlame(int numberOfSamples, int samplingRate) {
  return getRawValue() < FLAME_DETECTED_THRESHOLD;
}
