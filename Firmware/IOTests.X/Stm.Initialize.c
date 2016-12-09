#include "BuggyConfig.h"
#include "LEDs.h"
#include "Types.h"
#include "Uart.h"
#include "Timer.h"
#include "ESP8266.h"
#include "Counters.h"
#include "AnalogSensors.h"

// Add global variables here.
extern OnTimerInterrupt HandleTimerInterrupt_0;
extern OnTimerInterrupt HandleTimerInterrupt_1;
extern OnTimerInterrupt HandleTimerInterrupt_2;
 
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
            mInitializationState = Idle;
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
    RCONbits.IPEN = 1;    // Enable priority levels on interrupts
    
    InitializeLeds();
    InitCounters();
    InitMainTimer();
    InitAnalogSensors();
    
    if (!InitializeUart(57600))
    {
        return false;
    } 
  
    HandleTimerInterrupt_0 = UpdateLedState;
    HandleTimerInterrupt_1 = UpdateGeneralCounter;
    HandleTimerInterrupt_2 = UpdateAnalogSensorReadings;
    
    // Disable USB interrupt.
    PIE2bits.USBIE = 0;

    // Enable interrupts
    INTCONbits.GIEL = 1;  // Enable low priority interrupts
    INTCONbits.GIEH = 1;  // Enable high priority interrupts
    
    return true;
}