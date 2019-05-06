#ifndef TIMER
#define TIMER

#include "Constants.h"

/**
 * A single-use timer object that can be polled to see if
 * the specified duration has passed
 */
class Timer
{
private:
  double startTime;
  double durationInMS;

public:

  /**
   * Creates a new Timer object
   */
  Timer(int durationInMS = PIDConstants::COMMAND_TIMEOUT);
  
  /**
   * @return whether all the time in the timer has elapsed
   */
  bool isFinished();
};

#endif
