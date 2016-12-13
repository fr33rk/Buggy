#include "Types.h"
#include "Counters.h"
#include "ESP8266.h"

// Add global variables here.

// Add local variables here.
typedef enum _OPERATIONAL_STATE
{
    Idle,
    Start,
    SendingMessage,
    Finalize,
} enmOperationalState;

static enmOperationalState mCurrentState;

// Add function prototypes here.

/**
* The state machine when the module is in measure mode.
* @return True when STM busy, otherwise false.
*/
bool OperationalStateMachine(void)
{
    switch(mCurrentState)
    {
        case Idle:
            return false;
        case Start:
            SetTimer(0, 5000);
            mCurrentState = SendingMessage;
            return true;
        case SendingMessage:
            if (IsTimerExpired(0))
            {
                SendMessage("Hello world");
                ResetTimer(0);
                mCurrentState = Start;
            }
            return true;
        case Finalize:
            mCurrentState = Idle;
            return false;
        default:
            mCurrentState = Idle;
            return false;
    }
}

/**
 * Initialize the operational state machine.
 */
void InitOperationalStateMachine(void)
{
    mCurrentState = Idle;
}

/**
 * Start the operational state machine.
 * @return 
 */
bool StartOperationalStateMachine()
{
    if(mCurrentState == Idle)
    {
        mCurrentState = Start;
        return true;
    }
    //Busy
    return false;
}

