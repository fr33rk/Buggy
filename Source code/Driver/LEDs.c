#include "LEDs.h"
#include <pic18f4455.h>

void InitializeLeds()
{
    // Set all Port D ports to output
    TRISD = 0x00;
    
    // Turn off all LEDs
    LATD = 0x00;    
}

bool IsLEDSet(uint8_t index)
{
    uint8_t expectedValue = (1 << index);
    bool retValue = (PORTD & expectedValue) == expectedValue;
    return retValue;
}

void SetLED(uint8_t index, bool state)
{
    if (state)
    {
        LATD |= (1 << index);
    }
    else
    {
        LATD &= ~(1 << index);
    }
}

void SetByteValueInLED(uint8_t value)
{
    LATD = value;
}
