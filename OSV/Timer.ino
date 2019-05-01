#include "Timer.h"

Timer::Timer(int durationInMS) : startTime(millis()),
                                 durationInMS(durationInMS)
{
}

bool Timer::isFinished()
{
    return millis() - startTime >= durationInMS;
}