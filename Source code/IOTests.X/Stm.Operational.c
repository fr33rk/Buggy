#include "Types.h"
#include "Counters.h"
#include "ESP8266.h"

// Add global variables here.
typedef enum _OPERATIONAL_STATE
{
    Idle,
    Start,
    SendMessage,
    Finalize,
} enmOperationalState;


// Add local variables here.
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
            SetTimer(0, 1000);
            mCurrentState = SendMessage;
            return true;
        case SendMessage:
            if (IsTimerExpired(0))
            {
                //Send("Hello world");
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

 

void InitOperationalStateMachine(void)
{
    mCurrentState = Idle;
}

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

