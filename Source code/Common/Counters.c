#include "Types.h"

typedef struct COUNTER
{
    uint32_t Start;
    uint32_t End;
    bool IsRunning;
} Counter;

#define MAX_COUNTERS 3

uint32_t mGeneralCounter;
Counter mCounters[MAX_COUNTERS];

/**
 * Updates the general counter. Should be called each millisecond.
 */
void UpdateGeneralCounter()
{
    mGeneralCounter++;
}

/**
 * Initializes the counters 
 */
void InitCounters()
{
    mGeneralCounter = 0;
}

/**
 * Start a timer.
 * @param counterNo, the counter that needs to be started. (0..MAX_COUNTERS)
 * @param duration, the duration before the counter expires, in ms.
 * @return true, when the counter was successfully set.
 */
bool SetTimer(uint8_t counterNo, uint32_t duration)
{
    if ((counterNo < MAX_COUNTERS) && !mCounters[counterNo].IsRunning)
    {
        mCounters[counterNo].Start = mGeneralCounter;
        mCounters[counterNo].End = mGeneralCounter + duration;
        mCounters[counterNo].IsRunning = true;
        return true;
    }
    
    return false;
}

/**
 * Reset (free) a previously used timer.
 * @param counterNo, the counter that needs to be freed.
 * @return true, when the counter was reset successfully.
 */
bool ResetTimer(uint8_t counterNo)
{
    if ((counterNo < MAX_COUNTERS) && mCounters[counterNo].IsRunning)    
    {
        mCounters[counterNo].IsRunning = false;
        return true;
    }
    
    return false;
}

/**
 * Test if a timer has expired.
 * @param counterNo, the counter to check.
 * @return true, when the counter has expired.
 */
bool IsTimerExpired(uint8_t counterNo)
{
    if ((counterNo < MAX_COUNTERS) && mCounters[counterNo].IsRunning)
    {
        uint32_t startPos = mCounters[counterNo].Start;
        uint32_t endPos = mCounters[counterNo].End;
        
        if(startPos == endPos) 
        {
            return true;
        }

        if(endPos > startPos)
        {
            return (endPos < mGeneralCounter || mGeneralCounter < startPos);       
        }
        else
        {
            return (endPos < mGeneralCounter && mGeneralCounter < startPos);
        }             
    }
    return false;
}