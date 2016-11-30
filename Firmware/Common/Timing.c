#include <pic18.h>
#include "BuggyConfig.h"
#include "Timing.h"

/**
 * Synchronious delay in seconds.
 * @param s, amount of seconds. 
 */
void DelayS(uint8_t s)
{
    for (int i = 1; i <= s; i++)
    {
        DelayMs(i * 1000);
    }
}

/**
 * Synchronious delay in ms.
 * @param ms
 */
void DelayMs(uint16_t ms)
{
    for (int i = 0; i < ms; i++)
    {
        __delay_ms(1);
    }
}

