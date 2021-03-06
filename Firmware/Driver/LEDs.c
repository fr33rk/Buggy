#include "LEDs.h"
#include <pic18f4455.h>

// Add global variables here.
#define LED_ON_COUNT 250
#define LED_OFF_FAST_COUNT 500
#define LED_OFF_SLOW_COUNT 1000

// Add local variables here.
static volatile enmLedState mCurrentLedStates[8];
static uint16_t mLedOffCounter[8];
static uint16_t mLedOnCounter[8];
static volatile bool mFixedValueSet;

// Add function prototypes here.
void BlinkLed(uint8_t index, uint16_t ledOffCount);
void SetLed(uint8_t index);
void ClearLed(uint8_t index);

/**
 * Initialize the hardware to enable the LED's.
 */
void InitializeLeds()
{
    mFixedValueSet = false;
    
    // Set all Port D ports to output
    TRISD = 0x00;
    
    // Turn off all LEDs
    LATD = 0x00;    
}

/**
 * Set the LED state of one of the leds.
 * 
 * @param index, the LED that needs to be set. (0..7)
 * @param ledState, see the enum for possible states
 */
void SetLedState(uint8_t index, enmLedState ledState)
{
    switch(ledState)
    {
        case BlinkSlow:
        {
            mLedOnCounter[index] = LED_ON_COUNT;
            mLedOffCounter[index] = LED_OFF_SLOW_COUNT;
            break;
        }
        case BlinkFast:
        {
            mLedOnCounter[index] = LED_ON_COUNT;
            mLedOffCounter[index] = LED_OFF_FAST_COUNT;
            break;            
        }
        default:
        {
            break;
        }                
    }
    
    mCurrentLedStates[index] = ledState;
}

/**
 * Process the LED states that have been set via SetLedState.
 */
void UpdateLedState()
{
    if (!mFixedValueSet)
    {
        for (uint8_t index = 0; index < 8; index++)
        {
            switch(mCurrentLedStates[index])
            {
                case ContinuesOn:
                    SetLed(index);
                    break;
                case ContinuesOff:
                    ClearLed(index);
                    break;
                case BlinkSlow:
                    BlinkLed(index, LED_OFF_SLOW_COUNT);
                    break;
                case BlinkFast:
                    BlinkLed(index, LED_OFF_FAST_COUNT);
                    break;
                default:
                    break;    
            }
        }
    }
}

/**
 * Display a uint8_t value as binary value using the LEDs.
 * @param value, int value that needs to be displayed.
 */
void SetByteValueInLed(uint8_t value)
{
    mFixedValueSet = true;
    LATD = value;
}

/**
 * Clear the previouslt set byte value and return to 'normal' operation.
 */
void ClearByteValueInLed()
{
    mFixedValueSet = false;
}

/**
 * Turn led at index ON.
 * @param index
 */
void SetLed(uint8_t index)
{
    LATD |= (1 << index);
}

/**
 * Turn led at index OFF.
 * @param index
 */
void ClearLed(uint8_t index)
{
    LATD &= ~(1 << index);
}

void BlinkLed(uint8_t index, uint16_t ledOffCount)
{
	if(mLedOnCounter[index] != 0)
	{
		mLedOnCounter[index]--;
	}
	else if(mLedOnCounter[index] == 0)
	{
		ClearLed(index);

		if(mLedOffCounter[index] != 0)
		{
			mLedOffCounter[index]--;
		}
		else if(mLedOffCounter[index] == 0)
		{
			mLedOnCounter[index] = LED_ON_COUNT;
			mLedOffCounter[index] = ledOffCount;
			SetLed(index);			
		}
	}    
}