#include "BuggyConfig.h"
#include "LEDs.h"
#include "Types.h"
#include "Uart.h"
#include "Timer.h"
#include "ESP8266.h"
#include "Counters.h"

// Add global variables here.
extern OnTimerInterrupt HandleTimerInterrupt_0;
extern OnTimerInterrupt HandleTimerInterrupt_1;
 
// Add local variables here.
typedef enum INITIALIZE_STATE
{
    Idle,
    Start,
    InitializingBuggy,
    InitializingEsp,
    Finalize,
} enmInitializeState;

enmInitializeState mInitializationState;

// Add function prototypes here.
bool InitializeBuggy(void);

/**
* The state machine when the module is in measure mode.
* @return True when STM busy, otherwise false.
*/
bool InitializeStateMachine()
{
    switch (mInitializationState)
    {
        case Idle:
            return false;
        case Start:
            mInitializationState = InitializingBuggy;
            return true;
        case InitializingBuggy:
            InitializeBuggy();
            SetLedState(1, BlinkFast);
            InitInitializeEspStateMachine();
            StartInitializeEspStateMachine();
            mInitializationState = InitializingEsp;
            
            // Clear the communication buffers.
            UartSendString("Dummy");
            
            return true;
        case InitializingEsp:
            if (!InitializeEspStateMachine())
            {
                SetLedState(0, BlinkSlow);
                SetLedState(1, ContinuesOff);
                mInitializationState = Finalize;
            }
            return true;
        case Finalize:
            return false;
        default:
            return false;
    }
}

void InitInitializeStateMachine()
{
    mInitializationState = Idle;
}

bool StartInitializeStateMachine()
{
   if(mInitializationState == Idle)
   {
        mInitializationState = Start;
        return true;
    }
    //Busy
    return false;
}

bool InitializeBuggy()
{
    InitializeLeds();
    InitCounters();
    InitMainTimer();
    
    if (!InitializeUart(57600))
    {
        return false;
    } 
   
    HandleTimerInterrupt_0 = UpdateLedState;
    HandleTimerInterrupt_1 = UpdateGeneralCounter;
    
    // Disable USB interrupt.
    PIE2bits.USBIE = 0;
    
    INTCON3 = 0;
    INTCON2bits.RBPU = 0;
    INTCON = 0;
    
    // Enable interrupts
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;   // Global interrupt enable.

    return true;
}