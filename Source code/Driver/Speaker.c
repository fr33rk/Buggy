#include <pic18f4455.h>
#include "Speaker.h"
#include "Timing.h"

void EnableSpeaker()
{
    TRISC0 = 0x00;
}

void Beep(uint16_t duration)
{
    duration += 10 - duration % 10;

    for (uint16_t i = duration; i >0; i -= 10)
    {
        LATC0 = 1;
        DelayMs(5);
        LATC0 = 0;
        DelayMs(5);
    }
}



